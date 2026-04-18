#include "HX711.h"
#include "PDLS_Common.h"
#include "Pervasive_BWRY_Small.h"
#include "PDLS_Basic.h"

eScreen_EPD_t eScreen = eScreen_EPD_266_QS_0F;
Pervasive_BWRY_Small myDriver(eScreen, boardESP32DevKitC);
Screen_EPD myScreen(&myDriver);
uint8_t font = Font_Terminal12x16;

// Capteur 1 avec les branchements utilisés pour la balance du bac blanc
#define DT1 13
#define SCK1 14
HX711 scale1;

// Capteur 2 avec ceux du bac couleur
#define DT2 4
#define SCK2 5
HX711 scale2;

float calibration_factor = -434; // Déterminé dans un code de calibration au préalable
float weight1 = 0, weight2 = 0;
float lastWeight1 = 0, lastWeight2 = 0;

//  Seuils : 5 grammes de variation pour que l'écran s'actualise
//           150 grammes atteints au total pour que l'écran affiche le message prévu
const float seuilMassePrete = 150.0;
const float seuilVariation = 5.0;

// États de déclenchement si jamais l'un des deux capteurs détecte plus de 150 grammes
bool blancPret = false;
bool couleurPret = false;

void afficherMessageBienvenu() {
  myScreen.begin();
  myScreen.setOrientation(ORIENTATION_LANDSCAPE);
  myScreen.selectFont(font);
  myScreen.clear();

  String titre = "Tribac";
  uint16_t x1 = (myScreen.screenSizeX() - myScreen.stringSizeX(titre)) / 2;
  myScreen.gText(x1, 20, titre.c_str(), myColours.red);

  String ligneVide = " ";   // Pour le premier écran d'affichage quand le programme s'exécute
  uint16_t xv = (myScreen.screenSizeX() - myScreen.stringSizeX(ligneVide)) / 2;
  myScreen.gText(xv, 40, ligneVide.c_str(), myColours.black);

  String msg = "Bienvenue";
  uint16_t x2 = (myScreen.screenSizeX() - myScreen.stringSizeX(msg)) / 2;
  myScreen.gText(x2, 60, msg.c_str(), myColours.black);

  myScreen.flush();
}

void afficherTroisLignes(String l1, String l2, String l3) {
  myScreen.clear();

  myScreen.selectFont(font);
  uint16_t x1 = (myScreen.screenSizeX() - myScreen.stringSizeX(l1)) / 2;
  myScreen.gText(x1, 10, l1.c_str(), myColours.red); // "Tribac" en rouge

  myScreen.gText(10, 60, l2.c_str(), myColours.black);
  myScreen.gText(10, 85, l3.c_str(), myColours.black);

  myScreen.flush();
}

void afficherDeuxLignes(String ligne1, String ligne2) {
  myScreen.clear();

  myScreen.selectFont(font);
  uint16_t x1 = (myScreen.screenSizeX() - myScreen.stringSizeX(ligne1)) / 2;
  myScreen.gText(x1, 30, ligne1.c_str(), myColours.red); 

  uint16_t x2 = (myScreen.screenSizeX() - myScreen.stringSizeX(ligne2)) / 2;
  myScreen.gText(x2, 70, ligne2.c_str(), myColours.black);

  myScreen.flush();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Initialisation des capteurs HX711...");

  hV_HAL_begin();
  afficherMessageBienvenu();

  delay(2000); // Attente pour lecture bienvenue

  // Initialisation des capteurs
  scale1.begin(DT1, SCK1);
  scale1.set_scale(calibration_factor);
  scale1.tare();

  scale2.begin(DT2, SCK2);
  scale2.set_scale(calibration_factor);
  scale2.tare();

  Serial.println("Capteurs prêts.");
}

void loop() {
  if (scale1.is_ready() && scale2.is_ready()) {
    weight1 = scale1.get_units(5);
    weight2 = scale2.get_units(5);

    if (weight1 < 0) weight1 = 0;
    if (weight2 < 0) weight2 = 0;

    Serial.print("Masse capteur 1 : ");
    Serial.print(weight1);
    Serial.println(" g");

    Serial.print("Masse capteur 2 : ");
    Serial.print(weight2);
    Serial.println(" g");

    // Réinitialiser les états dans le cas où le poids redescend sous le seuil pour éviter les erreurs d'affichage
    if (weight1 < seuilMassePrete) blancPret = false;
    if (weight2 < seuilMassePrete) couleurPret = false;

    // Cas où les deux bacs sont prêts
    if (weight1 >= seuilMassePrete && weight2 >= seuilMassePrete && (!blancPret || !couleurPret)) {
      afficherDeuxLignes("Tribac", "Les deux bacs sont prets");
      blancPret = true;
      couleurPret = true;
    }
    // Cas où seul le bac blanc est prêt
    else if (weight1 >= seuilMassePrete && !blancPret) {
      afficherDeuxLignes("Tribac", "Le bac blanc est pret");
      blancPret = true;
    }
    // Cas où seul le bac couleur est prêt
    else if (weight2 >= seuilMassePrete && !couleurPret) {
      afficherDeuxLignes("Tribac", "Le bac couleur est pret");
      couleurPret = true;
    }
    // Cas où après le retrait, si l’un des bacs est encore prêt il faut le réafficher
    else if (weight1 >= seuilMassePrete && !couleurPret) {
      afficherDeuxLignes("Tribac", "Le bac blanc est pret");
      blancPret = true;
    }
    else if (weight2 >= seuilMassePrete && !blancPret) {
      afficherDeuxLignes("Tribac", "Le bac couleur est pret");
      couleurPret = true;
    }
    // Cas où une variation importante est détectée : affichage des poids
    else if (abs(weight1 - lastWeight1) >= seuilVariation || abs(weight2 - lastWeight2) >= seuilVariation) {
      char ligne2[30];
      char ligne3[30];
      snprintf(ligne2, sizeof(ligne2), "Bac blanc : %.1fg", weight1);
      snprintf(ligne3, sizeof(ligne3), "Bac couleur : %.1fg", weight2);
      afficherTroisLignes("Tribac", ligne2, ligne3);
    }

    lastWeight1 = weight1;
    lastWeight2 = weight2;
  } else {
    Serial.println("Erreur : un ou les deux capteurs ne sont pas prêts.");
  }

  delay(1000);
} 

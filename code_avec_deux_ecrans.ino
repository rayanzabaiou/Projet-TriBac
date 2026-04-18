#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "HX711.h"

// HX711 capteur 1
#define DT1_PIN 32
#define SCK1_PIN 33
HX711 scale1;

// HX711 capteur 2
#define DT2_PIN 25
#define SCK2_PIN 26
HX711 scale2;

float calibration_factor = -434;
float weight1 = 0;
float weight2 = 0;

// Bus I2C pour deux écrans
TwoWire I2CBus1 = TwoWire(0);
TwoWire I2CBus2 = TwoWire(1);

// Pins I2C
#define SDA_1 21
#define SCL_1 22

#define SDA_2 18
#define SCL_2 19

// Écrans OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &I2CBus1, OLED_RESET);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &I2CBus2, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Serial.println("Initialisation des capteurs HX711...");

  // I2C écrans
  I2CBus1.begin(SDA_1, SCL_1);
  I2CBus2.begin(SDA_2, SCL_2);

  // Initialisation OLED 1
  if (!display1.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erreur écran 1 !");
    while (true);
  }

  // Initialisation OLED 2
  if (!display2.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erreur écran 2 !");
    while (true);
  }

  display1.clearDisplay();
  display2.clearDisplay();
  display1.setTextSize(1);
  display2.setTextSize(1);
  display1.setTextColor(SSD1306_WHITE);
  display2.setTextColor(SSD1306_WHITE);

  display1.setCursor(0, 0);
  display1.println("Init capteurs...");
  display1.display();

  display2.setCursor(0, 0);
  display2.println("Init capteurs...");
  display2.display();

  // Initialisation capteurs
  scale1.begin(DT1_PIN, SCK1_PIN);
  scale1.set_scale(calibration_factor);
  scale1.tare();

  scale2.begin(DT2_PIN, SCK2_PIN);
  scale2.set_scale(calibration_factor);
  scale2.tare();

  delay(1000);
}

void loop() {
  // Lecture capteur 1
  if (scale1.is_ready()) {
    weight1 = scale1.get_units(5);
    if (weight1 < 0) weight1 = 0;
  } else {
    Serial.println("Erreur capteur 1");
  }

  // Lecture capteur 2
  if (scale2.is_ready()) {
    weight2 = scale2.get_units(5);
    if (weight2 < 0) weight2 = 0;
  } else {
    Serial.println("Erreur capteur 2");
  }

  float total = weight1 + weight2;

  // Affichage série
  Serial.print("Poids 1: ");
  Serial.print(weight1);
  Serial.print(" g | Poids 2: ");
  Serial.print(weight2);
  Serial.print(" g | Total: ");
  Serial.println(total);

  // Message à afficher sur 2 écrans
  String message = "Poids capteur 1: " + String(weight1, 1) + "g | Capteur 2: " + String(weight2, 1) + "g | Total: " + String(total, 1) + "g";

  // Répartition sur deux écrans
  String part1 = message.substring(0, 22);  // 22 caractères pour écran 1
  String part2 = message.substring(22);     // reste sur écran 2

  // Écran 1
  display1.clearDisplay();
  display1.setCursor(0, 0);
  display1.setTextSize(1);
  display1.println(part1);
  display1.display();

  // Écran 2
  display2.clearDisplay();
  display2.setCursor(0, 0);
  display2.setTextSize(1);
  display2.println(part2);
  display2.display();

  delay(1000);
}

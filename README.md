# TriBac - Le Bac à Linge Intelligent

> **Projet de 3ème année à l'ESIEE Paris.**
> Conception et fabrication d'un système automatisé de tri de vêtements par RFID et pesée intelligente.

---

## 💡 Le Concept
TriBac est une solution d'automatisation domestique conçue pour simplifier la corvée de tri du linge. Le système identifie chaque vêtement via une puce **RFID**, l'achemine via un système de **tapis roulants à trois niveaux**, et l'oriente vers le bac approprié (Blanc ou Couleur) grâce à une inversion du sens de rotation du tapis final.

### 🎯 Contraintes du projet :
* **Budget :** 150€ maximum.
* **Délai :** 2 mois (conception, commande, fabrication, tests).
* **Équipe :** 5 étudiants.

---

## 🛠️ Ma Contribution : Pesée & Interface Utilisateur
Sur ce projet, j'étais responsable de la conception et du développement de la **station de pesage et d'affichage**.

### 🔹 Système de pesée 
* Fabrication de deux balances sur-mesure pour les bacs de réception.
* Utilisation de **capteurs de force** (Jauges de contrainte) couplés à des modules **HX711** pour la conversion analogique-numérique.
* Étalonnage manuel des capteurs pour garantir une précision au gramme près.

### 🔹 Interface & Affichage 
* Développement sous **Arduino IDE (C++)** pour l'intégration de l'écran.
* Gestion d'un écran **E-Paper / OLED Pervasive Display** (plus lisible et économe en énergie).
* Logique d'alerte : Le système détecte et affiche en temps réel le poids de chaque bac et prévient l'utilisateur via l'écran dès qu'un seuil de remplissage est atteint.

---

## 📂 Contenu du Repo
Ce dépôt contient les deux itérations du code de gestion d'affichage :
* `code_final_Pervasive_Display.ino` : La version finale optimisée pour l'écran Pervasive Display.
* `code_avec_deux_ecrans.ino` : Prototype initial utilisant deux écrans OLED via bus I2C.

---

## 🔧 Stack Technique
* **Microcontrôleur :** ESP32 / Arduino.
* **Capteurs :** Lecteur RFID, Capteurs de poids SEN-HX711.
* **Actuateurs :** Moteurs pour tapis roulants (pilotés par pont en H).
* **Affichage :** Pervasive Displays (E-Paper) / SSD1306 (OLED).
* **Langage :** C++ (Arduino).

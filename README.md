# Projet-TriBac
Projet de création d'un bac à linge intelligent

En 2025, 5 étudiants de l'ESIEE Paris se sont lancé un défi : créer de A à Z un bac de tri de vêtements intelligent nommé TriBac. Le but du projet est de trier des vêtements en les mettant dans des bacs selont les différentes caractéristiques du vêtement, que ce soit selon sa couleur ou sa mtière par exemple. Bien entendu, comme pour tout projet universitaire, il y avait quelques contraintes, à savoir : 
- Des achats limités à quelques sites choisis par l'école et un budget de 150€,
- 2 mois pour tout faire : trouver l'idée du projet, passer les commandes, fabriquer la machine et la tester.

Chaque vêtement possède un tag RFID qui permet d'identifier sa couleur ou sa matière. On place ensuite plusieurs vêtements sur un tapis roulant (de 3 niveaux) qui va les espacer. Un lecteur RFID est présent au niveau du 2e étage du tapis roulant et va scanner chaque vêtement un par un. Selon l'information à laquelle correspond le tag scanné, le dernier étage du tapis roulant changera ou non de sens. Par exemple, si le vêtement est bleu, le dernier tapis tournera dans le sens horaire pour que le vêtement tombe dans le bac "couleur", et si le vêtement est blanc, il tournera dans le sens anti-horaire pour que le vêtement tombe dans le bac "blanc". Chaque bac est placé sur une balance que l'on a fabriquée avec des capteurs de force SEN-HX71105. Enfin, les deux balances sont liées à un écran d'affichage OLED Pervasive Display qui nous permet d'afficher à l'utilisateur des informations sur les différents bacs de tri.

Mon travail était de m'occuper de ces balances, en partant de leur confection, puis de leur calibration et enfin en codant sur l'IDE Arduino le code pour gérer l'affichage sur l'écran OLED.

Vous retrouverez donc le code utilisé pour gérer l'écran OLED Pervasive Display.
Toutefois, avant de décider d'utiliser l'écran Pervasive Display, nous avions essayé de paramétrer l'affichage sur deux petits écrans à bus I2C, vous trouverez également ce code dans le repo.

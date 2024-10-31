# Hackathon_2024
Dépôt pour le projet Hackathon 2024


## Avancée du projet

* Servomoteurs 360° opérationnels (vitesse contrôlée, sens aussi). Le robot peut rouler droit avec le bon réglage de vitesse de chaque côté.
* TOF Opérationnel. Placé à l'avant, ce sont les yeux du robot pour éviter des obstacles.
* Première version du chassis (v3) ok avec l'ensemble des composants.
* Prototype fait avec une breadboard soudable ok, un pcb est en conception.
* PCB en fabrication proto côté école

## Obstacles / Points délicats

* Passage sur STM32CubeIde complexe à envisager bien qu'il soit préférable. En effet l'utilisation d'un tof avec CubeIde est à creuser. Bof pour le capteur ultrasons (il voit moins loin et est moins fiable). Pour le TOF, la communication I2C est intéressante.

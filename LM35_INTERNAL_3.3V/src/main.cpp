/*
* Code d'exemple pour le capteur LM35 (2°C ~ +110°C) avec une meilleure précision.
https://www.carnetdumaker.net/articles/mesurer-une-temperature-avec-un-capteur-lm35-et-une-carte-arduino-genuino/


============================================================================
                                   ATTENTION !!!!!!!!!!!!!!!!!!!!!!!!!!!
NE RIEN CONNECTER SUR LA BROCHE AREF SI UNE TENSION DE REFERENCE INTERNE
                                 EST UTILISEE

Ne connectez rien à la broche AREF si une tension de référence interne est utilisée.

Si vous connectez quelque chose sur la broche AREF sans être dans le mode
EXTERNAL, vous allez déclencher un court-circuit à l'intérieur du microcontrôleur,
ce qui lui sera fatal
===========================================================================

Pour qu'un convertisseur analogique / numérique puisse faire son travail,
il a besoin d'une tension maximum de référence. Cette tension s'appelle AREF
par convention.
Avec une carte Arduino classique (Uno, Mega2560, etc.), il est possible de choisir la référence de tension en utilisant la fonction analogReference().

Dans notre cas, plusieurs choix sont possibles :
sur la Carte Arduino Uno :
- utiliser le mode EXTERNAL en reliant la broche AREF à la sortie +3V de la carte Arduino,
sur la carte Arduino Mega2560
- utiliser le mode INTERNAL (Arduino UNO) ou INTERNAL1V1 (Arduino Mega2560).

L'utilisation du mode EXTERNAL et de la broche AREF a l'avantage d'être générique.
Cela fonctionne sur n'importe quelle carte Arduino classique. Cependant,
la seule tension autre que 5 volts disponible sur une carte Arduino est de 3.3 volts.
Or, 3.3 volts / 1024 points (10 bits) = 3.23mV par point, c'est mieux, mais encore
loin d'être parfait.

autre possibilié :
On pourrait utiliser un montage avec une diode zener sur la broche AREF pour
générer une tension stable de 1.1 volt, mais cela serait un peu complexe.
Il est plus simple d'utiliser les modes INTERNAL et INTERNAL1V1, qui permettent
d'utiliser une tension de référence à 1.1 volt, interne au microcontrôleur.
Cela fonctionne que sur certaines cartes Arduino (UNO pour le mode INTERNAL)
Cela a l'avantage de ne demander aucune modification du montage de base.
*/
#include <Arduino.h>
// on définit les pins sur l'Arduino uno
const int lm35Pin = A0;

// on definit les variables
float temperature_celcius;
int valeur_brute;

// =============================== SETUP ===========================
// Fonction setup(), appelée au démarrage de la carte Arduino
void setup() {
pinMode(lm35Pin,INPUT);

Serial.begin(9600);   // Initialise la communication avec le PC

// Améliore la précision de la mesure en réduisant la plage de mesure
analogReference(INTERNAL);                 // Pour Arduino UNO
// analogReference(INTERNAL1V1); // Pour Arduino Mega2560
}

// *****************************
// on definit la fonction temperature
void mesuretemp () {
temperature_celcius = (1.1 * valeur_brute *100.0) / 1023;
}


// Fonction loop(), appelée continuellement en boucle tant que la carte Arduino est alimentée
void loop() {

// Mesure la tension sur la broche A0
valeur_brute = analogRead(A0);

// Transforme la mesure (nombre entier) en température via un produit en croix
//temperature_celcius = valeur_brute * (1.1 / 1023.0 * 100.0);

// on appelle la fonction définie en haut
mesuretemp();
// Envoi la mesure au PC pour affichage et attends 250ms
Serial.println(temperature_celcius,1);  // avec 1 décimale
delay(250);
} // fin du loop

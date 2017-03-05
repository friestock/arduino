/* éffacer un fichier sur une carte Micro SD break out +
 https://www.worldofgz.com/electronique/ecrire-et-lire-des-donnees-sur-une-carte-sd/
des données issus de capteur
mars 2017
*/

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// fichier de données
File fichierSD;

void setup() {
    pinMode(10, OUTPUT);


Serial.begin(9600);                 // Open serial communications and wait for port to open:
pinMode(10, OUTPUT);
while (!Serial) ;            // wait for serial port to connect. Needed for native USB port only
delay(1000); //1 sec


// initialisation de l'instance de la carte SD
if (!SD.begin(10)) {                    // si la carte n'est pas connectée au pin 10 alors ...
Serial.println("Echec de l initialisation !");
return;
}
Serial.println("Initialisation OK");   // la carte SD est connecté au pin 10

} // fin du setup

void loop() {

if (SD.exists("sensors.csv")) {                    // on teste la présence du fichier sensors.csv
Serial.println("Le fichier sensors.csv existe ");  // affichage à l'écran
}
else {
Serial.println("Le fichier sensors.csv n'existe pas encore"); // affichage à l'écran
}
SD.remove("sensors.csv"); // on efface le fichier

if (SD.exists("sensors.csv")) { // on reteste
Serial.println("Le fichier sensors.csv est toujours présent ");  // affichage à l'écran
}
else {
Serial.println("Le fichier sensors.csv est effacé "); // affichage à l'écran
}

}   // fin du loop

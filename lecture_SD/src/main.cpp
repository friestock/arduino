/*/ Lecture d'un fichier sur une carte Micro SD break out +
// mars 2017
// https://www.worldofgz.com/electronique/ecrire-et-lire-des-donnees-sur-une-carte-sd/




*/
// on définit les library
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// nom du fichier de données s'appelle fichierSD sur la carte microSD
File fichierSD;

// ============================== SETUP ===============================
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(9600);
pinMode(10, OUTPUT);
while (!Serial) ;                               // wait for serial port to connect. Needed for native USB port only
delay(1000); //1 sec

// initialisation de l'instance de la carte SD
if (!SD.begin(10)) {                    // si la carte n'est pas connecté au pin 10 alors ...
Serial.println("Echec de l initialisation !");
return;
}
Serial.println("Initialisation OK");   // la carte SD est connecté au pin 10

} // fin du setup

void loop() {

// on teste la présence du fichier sensors.csv
if (SD.exists("sensors.csv")) {// deprecated conversion from string constant to 'char*' [-Wwrite-strings]at line 255 col 28
Serial.println("Le fichier sensors.csv existe ");
}
else {
Serial.println("Le fichier sensors.csv n existe pas encore");
}
// on ouvre et affiche le fichier sensor
fichierSD = SD.open("sensors.csv", FILE_READ);

//La fonction available() va retourner chaque octet du fichier.
//Vous n’aurez qu’à boucler dessus pour afficher le contenu du fichier.
if(fichierSD) {
while (fichierSD.available()) {
Serial.write(fichierSD.read());
}
}
fichierSD.close();
delay(5000);

}   // fin du loop

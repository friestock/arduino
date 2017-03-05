/*Programme d’écriture de la température / luminosité sur carte SD



               Affichage Température du LM35 erronée





Voici le programme qu'il faut éditer dans l'IDE Arduino, puis compiler
et charger dans la carte Arduino. Il utilise une librairie.
La librairie SD pour écrire sur la carte est nativement fournie par l'IDE.

* SD card attached to SPI bus as follows:
CD = a rien pour l'instant , permet avec une resistance de detecter ou non la presence d'une carte SD
CS = pin 10
DI = pin 11
DO = pin 12
CLK = pin 13
GND = GND
5V = VCC

*/
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

//On definit les capteurs
// lumière = photorésistance
// température = LM35

int photocellPin = 0; // the cell and 10K pulldown are connected to a0
int photocellReading; // the analog reading from the analog resistor divider
const int lm35Pin = A1;
// on definit les variables
float temperature;
long iteration;
// nom du fichier sur la carte SD
File fichierSD;

// ========================= SETUP ==============================
void setup(){
// on definit les pins en entree / sortie
pinMode(lm35Pin,INPUT);
pinMode(10, OUTPUT);

// initialisation
Serial.begin(9600);
Serial.print("Initializing SD card...");

          if (!SD.begin(10)) {  // On vérifie que la carte SD est bien connectée au pin 10 de la carte arduino Uno
            Serial.println("initialization failed!");
            return;
          }
  Serial.println("initialization done.");

// on ouvre en ecriture un fichier nommé sensors.csv
  fichierSD = SD.open("sensors.csv", FILE_WRITE);
          if (fichierSD) {
                Serial.print("Initialisation du fichier sensors.csv...");
                fichierSD.println("  n° ;   lux   , temperature");              // on écrit l'entête
                fichierSD.close();                          // on ferme le fichier et donc l'entete sera écrite
                Serial.println("le fichier est créé, il est prêt à recevoir des données.");
              } else {
                Serial.println("error opening sensors.csv");
              }

  Serial.println("Luminosité et température sont mesurées, patience ...");
  delay(1000);   // wait for sensor initialization

  // loop
  iteration = 1; // compteur pour la boucle loop pour les mesures effectuées par les sondes

} // fin du setup

// on definit la fonction temperature pour des mesures de temperature
void mesuretemp () {
  temperature = (5.0 * analogRead(lm35Pin) *100.0) / 1024;
}
void mesurelux () {
  photocellReading = analogRead(photocellPin);
}

void loop() {
// on calcule la  luminosité et la temperature
mesurelux ();
mesuretemp();

String sIteration = String(iteration);
String sLumiere = String(photocellReading);
String sTemperature = String(temperature);

// on affiche la luminosité
  Serial.println("Lumière = " + sLumiere + " Temperature °C = "+ sTemperature);

// on ouvre et on écrit dans le fichier les variables collectées
  fichierSD = SD.open("sensors.csv", FILE_WRITE);
  if (fichierSD) {
    Serial.print("Ecriture des données dans le fichier sensors.csv...");

    fichierSD.println(sIteration + ";" + sLumiere + ";" + sTemperature);
    fichierSD.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening sensors.csv");
  }

  iteration++;
  delay(4000);
} // fin du loop

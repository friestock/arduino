/* écrire dans un fichier sur une carte Micro SD break out +
 https://www.worldofgz.com/electronique/ecrire-et-lire-des-donnees-sur-une-carte-sd/
https://www.arduino.cc/en/Tutorial/listfiles
des données issus de capteur


*/

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// capteurs
int photocellPin = 0; // the cell and 10K pulldown are connected to a0
int photocellReading; // the analog reading from the analog resistor divider
const int lm35Pin = A1;
float temperature;
long iteration;

// fichier de données
File fichierSD;
void setup() {
  // on definit l'état des pins de l'Arduino (INPUT ou OUTPUT)
  pinMode(photocellPin,INPUT); // justifié ????
  pinMode(lm35Pin,INPUT);
  pinMode(10, OUTPUT);

// Open serial communications and wait for port to open:
Serial.begin(9600);
pinMode(10, OUTPUT);
while (!Serial) ;                               // wait for serial port to connect. Needed for native USB port only
delay(1000); //5 sec

iteration = 1;      // on debute la numerotation des données de lux et temperature

// initialisation de l'instance de la carte SD
if (!SD.begin(10)) {                    // si la carte n'est pas connecté au pin 10 alors ...
Serial.println("Echec de l initialisation !");
return;
}
Serial.println("Initialisation OK");   // la carte SD est connecté au pin 10
// on va creer les entetes du fichier sensors.txt

// on teste la présence du fichier sensors.csv
if (SD.exists("sensors.csv")) {// deprecated conversion from string constant to 'char*' [-Wwrite-strings]at line 255 col 28
// Serial.println("Le fichier sensors.csv existe ");
}
else {
Serial.println("Le fichier sensors.csv n existe pas encore");


// on ouvre ou on crée n fichier sensors.csv
fichierSD = SD.open("sensors.csv", FILE_WRITE);
Serial.println("Le fichier sensors.csv est cree");
Serial.println("on etiquette");
fichierSD.println("n° ; Lumiere ; Température °C " );
fichierSD.close();
}
Serial.println("  n°  ; Lumiere  ; Température °C " );



  } // fin du setup

// on definit la fonction temperature pour des mesures de temperature
void mesuretemp () {
  temperature = (5.0 * analogRead(lm35Pin) *100.0) / 1024;
}
void mesurelux () {
// on calcule la  luminosité et la temperature
photocellReading = analogRead(photocellPin);
}



void loop() {
// on teste la présence du fichier sensors.csv
if (SD.exists("sensors.csv")) {// Serial.println("Le fichier sensors.csv existe ");
}
else {
Serial.println("Le fichier sensors.csv n existe pas encore");
}
// appel aux fonctions de mesure la lux et la temperature
mesurelux();
mesuretemp();

// on ouvre en ecriture un fichier nommé sensors.csv
  fichierSD = SD.open("sensors.csv", FILE_WRITE);
          if (fichierSD) {
              //  Serial.print("Initialisation du fichier sensors.csv...");  // affichage à l'écran

                String sIteration = String(iteration);
                String sLumiere = String(photocellReading);
                String sTemperature = String(temperature);
                fichierSD.println(sIteration + ";" + sLumiere + ";" + sTemperature);

                 //fichierSD.println("loop;photocellreading, temperature");   // ecriture dans fichierSD
                fichierSD.close();                                         // fermeture du fichier SD
              //  Serial.println("n° " +le fichier est créé, il est prêt à recevoir des données."); // affichage à l'écran
                Serial.println(" " +sIteration +" ; "+ sLumiere + " ; " + sTemperature);

              } else {
                Serial.println("error opening sensors.csv"); // affichage à l'écran
              }

// on recommence pour la donnée suivante
iteration++;
delay(5000);  // on attend 5 secondes entre 2 mesures

}   // fin du loop

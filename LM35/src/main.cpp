/* Utilisation du capteur de température en 5v
mesure la température et affiche la sur la console


*/
// on n'oublie pas de déclarer la library

#include <Arduino.h>
// on definit les pins utilisés
const int lm35Pin = A1;// On définit le port de branchement du LM35 en A1

// on définit la variable
float temperature;

// ========================== SETUP ==================================
void setup(){
pinMode(lm35Pin,INPUT);  // Pin Analogique A1 près à recevoir une donnée, donc en INPUT

// initialisation du port de communication
Serial.begin(9600);
} // fin du SETUP

// routine pour le calcul de la température
void mesuretemp () {
temperature = (5.0 * analogRead(lm35Pin) *100.0) / 1024;
}


void loop(){
mesuretemp();
String sTemperature = String(temperature); // temperature sera transformer en String
                                          // pour êtransformerincorporé dans le println
                                          // sinon cela bloque
// autre solution ce serait d'écrire
//Serial.print("la température est de : ");
//Serial.println(température );

Serial.println("la température est de : " + sTemperature);

delay(3000);
}

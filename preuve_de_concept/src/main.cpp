/* Projet arrosage plantes carnivores

Etape 0 : Preuve de concept

materiel de test :
1 capteur de température =LM352 boutons poussoirs
2 leds

//============== Objectif =======================
mesurer le taux d"humidité de l'espace de culture
mesurer la température
ventiler s'il fait trop chaud
augmenter l'humidité par brumisation de l'espace


capteur de température (LM35) sur le pin analogique A0 de l'Arduino
faux capteur d’humidité de l’air     pin 13 et 12
faux ventilateur (g à droite)        pin 10
faux brumisateur                     pin 9
fausse lampe                         pin 8
*/

// on déclare la library
#include <Arduino.h>
// const int permet de definir les broches comme fixe
const int buttonLeftPin =13;
const int buttonRightPin =12;

const int ledBrumisateurPin = 9;
const int ledFanPin = 10;
const int temperatureSensorPin = A0;

// on définit les variabkes, les seuils de déclenchement
int hygrometry = 50;
int previousHygrometry = -1;
int hygrometryMin = 60;

float temperature =20;
//float temperatureMin =22;
float temperatureMax= 25;

// on definit le temps
int milliseconds = 0;
// =============================== SETUP ============================
void setup(){
// vitesse de transmission des données
    Serial.begin(9600);
    // on definit l'état INPUT ou OUTPUT des broches
    pinMode(buttonLeftPin,INPUT);
    pinMode(buttonRightPin,INPUT);
    pinMode(ledBrumisateurPin, OUTPUT);
    pinMode(ledFanPin, OUTPUT);

} // fin du setup

// On définit la fonction temperature
void measureTemperature(){
    temperature = (5.0 * analogRead(temperatureSensorPin) * 100.0) / 1024;
}

// On definit la fonction d'allumer le ventilateur
void startFan () {
  digitalWrite(ledFanPin, HIGH);
}
// On definit la fonction d'éteindre le ventilateur
void stopFan () {
  digitalWrite(ledFanPin, LOW);
}

// On définit la fonction de mesurer le taux d'humidité
void measureHygrometry () {
  if(digitalRead(buttonLeftPin) == HIGH) {
    if (hygrometry >= 30) {
      hygrometry = hygrometry - 30;
    } else {
      hygrometry = 0;
    }
    delay(500);
  }

  if(digitalRead(buttonRightPin) == HIGH) {
    if (hygrometry <= 70) {
      hygrometry = hygrometry + 30;
    } else {
      hygrometry = 100;
    }
    delay(500);
  }

}
// On définit la fonction de declenchement de la brumisation
void startFogger () {
  digitalWrite(ledBrumisateurPin, HIGH);
}
// On definit la fonction arrêt de la brumisation
void stopFogger () {
  digitalWrite(ledBrumisateurPin, LOW);
}


void loop (){
// on appel les 2 sous-programmes : Hygrometry et Temperature
  measureHygrometry();
  measureTemperature();
// on vient de calculer les variables temperature et hygrometry
// on lance ou pas le Fogger en fonction de la valeur de l'hygrometry
  if(hygrometry < hygrometryMin) {
    startFogger();
  } else {
    stopFogger();
  }
// on lance ou pas le Fan en fonction de la valeur de la température
  if(temperature >  temperatureMax){
    startFan();
  }else{
    stopFan();
  }
// on affiche les résultats sur le Terminal toutes les 1s
// tout s'affichera sur une seule ligne
  if (milliseconds >= 1000) {
    Serial.print("hygrometrie = ");
    Serial.print(hygrometry);
    Serial.print(" % ");
    Serial.print("temperature = ");
    Serial.print(temperature);
    Serial.println(" °C");

    milliseconds = 0;
  }
// on redemarre un nouvel affichage lorsque 10 boucles auront été réalisées
  milliseconds += 100;
  delay(100);
}

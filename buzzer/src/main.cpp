/* fonctionnement d'un buzzer
fevrier 2017
matériel :
1 buzzer
1 bouton poussoir

Objectif : Si on appye sur bouton , le buzzer se déclenche

*/
// on n'oublie pas cette library
#include <Arduino.h>

int buzzer=7;            // on definit le pin 7  de l'Arduino pour le buzzer
const int buttonPin =10; // on definit le pin 10 pour le bouton d'appel !

// =========================== SETUP ===========================
void setup(){
pinMode(buzzer,OUTPUT);                    //la broche 7 digital en OUTPUT

// vitesse de transmission des données
Serial.begin(9600);
// on definit l'état INPUT de la broche 10 en entrée du bouton poussoir
pinMode(buttonPin,INPUT);

} // fin du setup

// On définit le sous programme buzzer
void lancebuzzer(){
tone(buzzer, 400);
}

void loop(){
//lecture de l'état du bouton et stockage dans etatBouton
boolean etatBouton = digitalRead(buttonPin);
//test des conditions
if (etatBouton==HIGH)            //test si bouton appuyé
{
lancebuzzer();                   // on allume le buzzer
}
if (etatBouton==LOW)            //test si bouton levé
{
noTone(buzzer);                 // on eteint le buzzer
}
delay(100); //petite attente
} // fin du loop

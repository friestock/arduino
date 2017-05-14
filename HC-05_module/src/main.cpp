
/*
*******************************************************************************
*        COMMUNICATION BLUETOOTH    telephone   <-----> HC-05 / Arduino       *
*******************************************************************************

    Le maître se met en mode « reconnaissable » = telephone portable
    L’esclave  (HC-05) trouve le maître et demande à s’y connecter
    Le maître accepte la connexion
    Les périphériques sont alors appairés (ou associés)
    La communication peut commencer.













matériel :
- module bluetooth HC-05
- Arduino uno
- 2 resistances de 4,7 k (jaune-violet-rouge) afin de limiter le courant <3,3 v
                         ( = le diviseur de tension pour la liaison RXD à TX )
- utilisation des pins TX=11 et RX=10
- telephone Android avec application
- led au pin13 digital

********************************************************************************
*                                CONFIGURATION                                 *
********************************************************************************

GND(arduino) ------------R1=4.7k ---------R2=4.7K ----TX(Arduino)
                                  /
                             RX (module HC-05)

RX(arduino) ----------- TX(module HC-05)
VCC = 5v

- pas de librairie à installer
http://howtomechatronics.com/tutorials/arduino/arduino-and-hc-05-bluetooth-module-tutorial/
https://igniteinnovateideas.wordpress.com/2016/04/18/arduino-bluetooth-basic-tutorial/
*/
#include <Arduino.h>


/***	Définition des variables		***/
int state = 0;
const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600); // envoi des données texte sur le terminal de l'ordi via l'USB
                     // mais aussi sur le telephone en bluetooth !!
                     // ne pas depasser 9600, sinon ne fonctionne pas
                    // le HC-05 n'est pas configuré pour fonctionner plus rapidement
}
void loop() {
  if(Serial.available() > 0){ // réception des données via le serial port du HC-05
    state = Serial.read(); // Reads the data from the serial port
 }
 if (state == '0') {
  digitalWrite(ledPin, LOW); // Turn LED OFF
  Serial.println("LED: OFF"); // Send back, to the phone et à l'ordi , the String "LED: ON"
  state = 0;
 }
 else if (state == '1') {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED: ON");
    state = 0;
 }
}

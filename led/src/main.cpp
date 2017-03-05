/* Allumer une led 2 sec , eteindre 2 secondes
brancher fil rouge (+) de la led sur pin 10
        fil noir (-) sur le GND de l'arduino
c'est basique, mais on commence par là !
Richard 2017
*/

// On commence par indiquer les bibliothèque (library) qui seront utilisées
// la première celle-ci
#include <Arduino.h>

const int ledPin = 10;   // pin digital 10 sur l'arduino

// ======================== SETUP ===============================
void setup() {
  // Open serial communications and wait for port to open:
//  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);   // il faut donc que du 5v sorte par le pin 10 pour allumer la ledPin
                            // donc en OUTPUT
} // fin du setup

void loop(){               // on boucle avec le loop Ad vitam æternam

digitalWrite(ledPin, HIGH);   // on donne du 5V , led s'allume
delay (2000);
digitalWrite(ledPin, LOW);    // on supprime le 5V , led s'éteint
delay (2000);                 // on attend 2 sec

} // fin du loop

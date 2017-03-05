/* affichage sur un LCD_PVC160101P d'ancienne génération
 lcd 16 x1  (16 caractères sur 1 ligne)
 pas de rétroéclairage. donc pas de A et K en 13 & 14 du lcd
 soit 1 ligne

mars 2017
NOTA : programme fonctionnel, mais de grande variation de température
avec le lm35. T°C= 14°C à 40 °C
à revoir

library : LiquidCrystalFast Library

// ********************** ma version ***********************
LiquidCrystalFast lcd(rs, rw, enable, d4, d5, d6, d7);
The circuit:
* LCD RS pin to digital pin 0       0 remplace 12
* LCD RW pin to digital pin 9       9 remplace 10
* LCD Enable to digital pin 1   1 remplace 11
* LCD d4 pin to digital pin 2       2 remplace 5
* LCD d5 pin to digital pin 3       3 remplace 4
* LCD d6 pin to digital pin 4       4 remplace 3
* LCD d7 pin to digital pin 5       5 remplace 2
* potentiometre de 10K ohms sur LCD broche 3 -V0
* VCC +5V and VSS GND
// *************** ma version *************************

En mode 4 bits, les broches à connecter à l’Arduino sont donc  :
RS, EN, DB4, DB5, DB6 et DB7 ainsi que, de façon optionnelle, RW.

// ****************************************************

Library originally added 18 Apr 2008
by David A. Mellis
library modified 5 Jul 2009
by Limor Fried (http://www.ladyada.net)
example added 9 Jul 2009
by Tom Igoe
modified 25 July 2009
by David A. Mellis

http://www.pjrc.com/teensy/td_libs_LiquidCrystal.html
http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

// include the library code:
#include <Arduino.h>
#include <SPI.h>
#include <LiquidCrystalFast.h>

// initialize the library with the numbers of the interface pins
LiquidCrystalFast lcd(0, 9, 1, 2, 3, 4, 5);
         // LCD pins: RS  RW  En  D4 D5 D6 D7

//On definit les pin sur l'Arduino
// lumière = photorésistance
// température = LM35

int photocellPin = 0; // the cell and 10K pulldown are connected to a0
const int lm35Pin = A1;

// les variables
int photocellReading; // the analog reading from the analog resistor divider
float temperature;


// ================================ SETUP =============================

void setup() {
  pinMode(lm35Pin,INPUT);


  // set up the LCD's number of columns (16) and rows (2):
  lcd.begin(8, 2);                      // test avec écran à 1 ligne !!! ça fonctionne
                                        // tout le texte s'affiche sur 1 ligne de 16 caractères
  lcd.clear();                          // on nettoie l'écran
  lcd.setCursor(0, 0);                 //ici, on se positionne en colonne 0, ligne 0
  lcd.print("**** BONJOUR ****");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("mesures :Lux / T");      // Print a message to the LCD.

  delay (2000);                       // on attend 2 s
  lcd.clear();                        // on nettoie l'écran

} // fin setup

// on definit la fonction temperature
void mesuretemp () {
  temperature = (5.0 * analogRead(lm35Pin) *100.0) / 1024;
}
// on definit la fonction mesur lumière
void mesurelux () {
  photocellReading = analogRead(photocellPin);
}

void loop() {
  // on calcule
 mesurelux();
 mesuretemp();

// on traite pour le lcd
  lcd.setCursor(0, 0);            // on se place au début
// au lieu d'ecrire le tout sur une ligne et de convertir en String les valeurs numériques
// on écrit sur 2 lignes qui s'écriront sur 1 seule ligne de 16 caractères
  lcd.print("Lum:");
  lcd.print(photocellReading);
  lcd.print(" Tc:");
  lcd.print(temperature);

  delay(2000);
  lcd.clear();

  delay(1000);

} // fin loop

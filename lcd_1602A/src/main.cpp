/*
Utilisation d'un lcd 1602A
librairy : LiquidCrystalFast Library

1er test : afficher le texte : "Temp :  Lum :"

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
* 10K ohms resistor  potentiometre   sur LCD broche 3 -V0
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)
// *************** ma version *************************

Paramètres :
Les paramètres sont les broches de l’Arduino qui sont reliées
aux broches du LCD (RS, RW...)
rs
rw (optionnel)
enable
d0, d1, d2, d3, d4, d5, d6, d7.
d0, d1, d2, et d3 sont optionnels ; si ils sont omis,
le lcd sera commandé avec les quatre dernières broches (d4 à d7).

RW or not RW
Cette broche peut être ou ne pas être employée.
Son rôle est de permettre la consultation du registre de contrôle du LCD.
En consultant le registre de contrôle, on sait si le LCD est disponible
pour recevoir des commandes ou des données ou si il est occupé à dessiner
des caractères sur l’écran. Si cette information manque, il faudra attendre
un certain temps entre deux commandes ou données afin d’être sur que le LCD
est disponible.
L’envoi d’information au LCD est donc plus lent mais on économise une broche.

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
#include <SD.h>
#include <LiquidCrystalFast.h>

// initialize the library with the numbers of the interface pins
LiquidCrystalFast lcd(0, 9, 1, 2, 3, 4, 5); // LCD pins: RS  RW  En  D4 D5 D6 D7

// ================================= SETUP ============================
void setup() {
  // set up the LCD's number of columns (16) and rows (2):
  lcd.begin(16, 2);
  lcd.clear();  // on nettoie l'écran
  lcd.setCursor(0, 0); //ici, on se positionne en haut à gauche de l'écran
  lcd.print("Temp :  Lum :"); // Print a message to the LCD.
  delay (5000);                // affichage 5 secondes
  lcd.clear();                // on efface
  delay (2000);                // pas de texte pendant 2 secondes
  lcd.print("Temp :  Lum :"); // On reaffiche le message sur le LCD.
} // fin setup

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // en dessous à gauche le décompte de temps
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000); // chronomètre
} // fin loop



/*
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup(){

    // set up the LCD's number of columns and rows:
    lcd.begin(16,2);

} //end "setup()"

void loop(){
lcd.clear();
lcd.setCursor(0, 0); //ici, on se positionne en haut à gauche de l'écran
lcd.print("Hello, funLAB!!!"); //Le texte qu'on affiche sur l'écran à l'endroit positionné
//delay(500); //On attend 500ms
lcd.clear();
  lcd.print("Hello world!");
  lcd.setCursor(0,1); //on passe à la ligne suivante
  lcd.print("OPENCLASSROOMS");
} // end loop()

*/



// ****************************************************************************
/*
/tmp/ccfHuOva.ltrans0.ltrans.o: In function `main':
ccfHuOva.ltrans0.o:(.text.startup+0x86): undefined reference to `setup'
ccfHuOva.ltrans0.o:(.text.startup+0x8e): undefined reference to `loop'
collect2: error: ld returned 1 exit status
*** [.pioenvs/uno/firmware.elf] Error 1
========================== [ERROR] Took 0.85 seconds ==========================


PlatformIO: BuildFile 0Project 0No Issuessrc/main.cpp20:13
LFUTF-8C++4 updates

=======================================================
/tmp/ccfHuOva.ltrans0.ltrans.o: In function `main':
ccfHuOva.ltrans0.o:(.text.startup+0x86): undefined reference to `setup'
ccfHuOva.ltrans0.o:(.text.startup+0x8e): undefined reference to `loop'
collect2: error: ld returned 1 exit status
*** [.pioenvs/uno/firmware.elf] Error 1
========================== [ERROR] Took 0.85 seconds ==========================


PlatformIO: BuildFile 0Project 0No Issuessrc/main.cpp20:13
LFUTF-8C++4 updates
*/

/*
Commande intrarouge à l'aide d'une télécommande
matériel :
- une telecommande (voir image) -pile CR2025 ou CR2032 à 3V
- une led réceptrice (modèle AX-1838HS)  3 broches :
vue de face :
      * gauche = out à brancher sur pin 11 de l'arduino
      * centre = masse
      * droite = VDD = 5V de l'arduino

- une led sandard avec sa résistance de 470 ohms (jaune / violer/marron)

touche 0,1,2,3,4,5,6,7,8,9 définies

*********************************************************************
*  NE PAS OUBLIER de créer un répertoire IRremote pour sa library   *
*    de même un autre dossier IRremoteInt pour son autre library    *
*********************************************************************

https://arduino-info.wikispaces.com/file/view/IR-Receiver-AX-1838HS.pdf/264668680/IR-Receiver-AX-1838HS.pdf

https://github.com/pauly/arduino/tree/master/libraries/IRremote
https://itechnofrance.wordpress.com/2013/04/19/librairie-irremote-pour-arduino/
https://www.kzenjoy.net/2015/votre-telecommande-universelle-grace-a-arduino/

bug : apparition de warning : large integer implicity to unsigned type (-Woverflow) at line 60 col 5
fonctionnel le 12/03/17
RF
*/

#include <Arduino.h>
#include <IRremote.h>         //adds the library code to the sketch : folder =IRremote
#include <IRremoteInt.h>      //  new folder =IRremoteInt

#define code0 0xFF6897  // touche 0 , idem pour les autres
#define code1 0xFF30CF
#define code2 0xFF18E7
#define code3 0xFF7A85

#define code4 0xFF10EF
#define code5 0xFF38C7
#define code6 0xFF5AA5

#define code7 0xFF42BD
#define code8 0xFF4AB5
#define code9 0xFF52AD

int broche_reception = 11;              // broche 11 utilisée
const int ledPin = 13;                 // on teste avec une led pour vérifier la bonne réception de l'IR
IRrecv reception_ir(broche_reception); // crée une instance
decode_results decode_ir;              // stockage données reçues

boolean lightState = false;
unsigned long last = millis();

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  reception_ir.enableIRIn();            // démarre la réception
} // fin du setup

void loop()
{
  if (reception_ir.decode(&decode_ir))
  {
  unsigned int codex = decode_ir.value;
  {
                                       // allumage d'une led pour confirmation de la reception
    if (millis() - last > 250) {
        //has it been 1/4 sec since last message
        lightState = !lightState;
        //toggle the LED
        digitalWrite(ledPin, lightState); // elle reste allumé tant que
                                        //l'on n'a pas appuyé sur une autre touche
        } // fin du if

    switch(codex) {
    case code0:
      Serial.println(" touche 0 appuyée");
      break;
    case code1:
      Serial.println(" touche 1 appuyée");
      break;
    case code2:
      Serial.println(" touche 2 appuyée");
      break;
    case code3:
      Serial.println(" touche 3 appuyée");
      break;
    case code4:
      Serial.println(" touche 4 appuyée");
      break;
    case code5:
      Serial.println(" touche 5 appuyée");
      break;
    case code6:
      Serial.println(" touche 6 appuyée");
      break;
    case code7:
      Serial.println(" touche 7 appuyée");
      break;
    case code8:
      Serial.println(" touche 8 appuyée");
      break;
    case code9:
      Serial.println(" touche 9 appuyée");
      break;
    default:
      Serial.println(" autre touche non programmée");
      break;
} // fin du switch

Serial.println(decode_ir.value, HEX);
  //  last = millis(); cela déclenche l'apparition de FFFFFF
  delay(1000);                         // on préfère attendre 1 s
    reception_ir.resume();            // reçoit le prochain code

} // fin du unsigned int
} // fin du if
} // fin du loop

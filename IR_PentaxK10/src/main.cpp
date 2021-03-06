
/* déclenchement d'un Pentax  KX à l'aide du led IR
Richard 26/03/17 fonctionnel.
Quand on appuye sur le bouton poussoir , le KX placé en mode infrarouge prend
une photo
matériel :
1 led de contrôle  1 resistance R= 220 ohms (rouge/rouge/noir)
1 led IR  emettrice + 1 resistance R= 181 ohms (marron / gris / marron)
1 bouton poussoir1 resistance R= 10 ko pour pull up ainsi qd on appuye sur le
bouton poussoir, on obtient une sortie =1

librairies :
MultiCameraIrControl.cpp et .h à placer dans un repertoire propre le tout
dans le répertoire lib

montage dans le répertoire /doc /img



http://sebastian.setz.name/arduino/my-libraries/multi-camera-ir-control/
https://github.com/dsebastien/electronicsProjects/tree/master/RemoteDSLRTrigger
images mises en film : https://www.dsebastien.net/2015/01/25/simple-time-lapse-using-ffmpeg/
Simple time-lapse using ffmpeg
http://playground.arduino.cc/Code/InfraredReceivers
https://wiki.turmlabor.de/projekte/dslrfernausloeser
http://www.righto.com/2009/08/multi-protocol-infrared-remote-library.html
=====================================================================
*/

#include<Arduino.h>
#include <multiCameraIrControl.h> // Camera IR control

Pentax K7(9);                // Pin 9 définit pour l'IR en INPUT
const int pinBouton=10;     // Pin 10 pour la led-bouton poussoir
const int pinled=7;         // permet la vérification du fonctionnement du bouton poussoir
                            // si on appuye sur le bouton poussoir , la led s'allume et
                            //la photo sera prise
 void setup(){
      //pinMode(Pentax K7,OUTPUT); //la broche 10 digital en OUTPUT

 Serial.begin(9600);        // vitesse de transmission des données à l'écran pour vérification
       pinMode(pinBouton,INPUT); // on definit l'état INPUT de la broche 10 en entrée du bouton poussoir
       pinMode(pinled,OUTPUT); // on definit l'état OUPUT de la broche 7 en sortie de la led
 }

 void loop(){
   //lecture de l'état du bouton et stockage dans etatBouton
     boolean etatBouton = digitalRead(pinBouton);

     //test des conditions
     if (etatBouton==HIGH)//test si bouton appuyé
     {
       digitalWrite(pinled,HIGH);          // on allume la led
       K7.shutterNow();                    // on prend une photo
      //  K7.toggleFocus();                // ne fonctionne pas
      delay(5000);                         // on attend 5 s
     }
     if (etatBouton==LOW)//test si bouton levé
     {
         digitalWrite(pinled,LOW);  // on eteint la led
     }
         Serial.print("Bouton poussoir à l'état : ");
         Serial.println(etatBouton);
         delay(1000); //petite attente
/*
   K7.shutterNow();
   delay(5000);
   K7.toggleFocus(); // ne fonctionne pas à revoir
   delay(5000);
   K7.toggleFocus();
   delay(5000);
   K7.toggleFocus();
   delay(5000);
   */
 }

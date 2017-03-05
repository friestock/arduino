/* fonctionnement d'un servo-moteur PS-348

Commande du servo-moteur PS-348 par impulsion
matériel :
1 servo-moteur
1 led
*/

// on definit les librairy
#include <Arduino.h>
#include <Servo.h>

// On définit les variables
int periode=20000;            // période entre chaque début d'impulsion en microsecondes
int pinServo=8;               // le servo est connecté au pin 8 de l'arduino
const int ledPin = 13;        // une led branchée sur le pin digital 13 de l'arduino

//=========================== SETUP =================================
void setup() {
  pinMode(pinServo,OUTPUT);             // on prépare le pin en mode OUTPUT
  digitalWrite(pinServo,LOW);          // on l'initialise à l'état bas
  pinMode(ledPin ,OUTPUT);             //pin 13 en mode OUTPUT

} // fin du setup

//On définit la fonction setAngle pour envoyer les impulsions
void setAngle(int a){
/*
Et voici comment le servo-moteur va interpréter ces impulsions :
    Lors d'une impulsion à 1ms : le servo-moteur se met à la position 0°,
    Lors d'une impulsion à 1.5 ms : le servo-moteur se met à la position 90°,
    Lors d'une impulsion à 2ms : le servo-moteur se met à la position 180°.

On peut donc facilement faire un mappage des valeurs pour obtenir pour obtenir la durée de l'impulsion en fonction de l'angle :
*/
  int duree=map(a,0,179,500,2500);// on transforme l'angle en microsecondes et
                                 // on stocke dans la variable duree
  digitalWrite(pinServo,LOW);    //on met le pin à l'état bas

  // la boucle qui suit est nécessaire
  // pour laisser le temps au servo d'aller à sa position
  for (int t=0;t<300;t++){
    digitalWrite(pinServo,HIGH);                   // on envoie l'impulsion
    delayMicroseconds(duree);                     // pendant la bonne durée
    digitalWrite(pinServo,LOW);                   // on stoppe l'impulsion
    delayMicroseconds(periode-duree);             // on attend le temps restant pour atteindre la période
  }
} // fin setAngle

// on definit la fonction allumer la ledPin
void diode13(){
  // on fait clignoter 5 fois la LED 13
  for (int t=0;t<5;t++){
    digitalWrite(ledPin,HIGH);
    delay(100);
    digitalWrite(ledPin,LOW);
    delay(100);
  }
} // fin diode13


void loop() {

  for (int angle=0;angle<=179;angle+=10){//on fait varier l'angle de 0 à 180° par tranche de 20°
    setAngle(angle);// on appelle la fonction setAngle définie plus bas
    diode13();
  }
} // fin du loop

/* ==================     Pour un autre programme =============================
int pinServo=8; // variable pour stocker le pin pour la commande
Servo leServo; // on définit un objet Servo nommé leServo

void setup() {
  leServo.attach(pinServo); // on relie l'objet au pin de commande
  pinMode(13,OUTPUT); //pin 13 en mode OUTPUT
}

void loop() {
  leServo.write(0); // on dit à l'objet de mettre le servo à 0°
  delay(2000); // ce délai est nécessaire pour que le servo atteigne sa position
  leServo.write(179); // position à 179, 180 est à éviter car cela forcerait le servo à dépasser ses limites
  delay(1000); // attente à nouveau
}
*/

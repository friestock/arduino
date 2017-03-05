/* Utilisation du cateur à ultrasons HC-SR04
Objectif : si on s'approche trop près du capteur à moins de 10 cm ,
la led rouge s'allume

VCC to arduino 5v
GND to arduino GND
Echo to Arduino pin 7
Trig to Arduino pin 8

LEDPinrouge = 13
LEDPinvert = 12
This sketch originates from Virtualmix: http://goo.gl/kJ8Gl
Has been modified by Winkle ink here: http://winkleink.blogspot.com.au/2012/05/arduino-hc-sr04-ultrasonic-distance.html
And modified further by ScottC here: http://arduinobasics.blogspot.com.au/2012/11/arduinobasics-hc-sr04-ultrasonic-sensor.html
on 10 Nov 2012.
RF Février 2017
*/
// on n'oublie par la library
#include <Arduino.h>

// on définit les pin sur l'Arduino
int echoPin = 7;            // Echo Pin
int trigPin = 8;           // Trigger Pin
int LEDPinrouge = 13;      // Onboard LED rouge
int LEDPinvert = 12;       // Onboard LED verte
int maxdist=10;           // si distance < maxdist la led rouge s'allume
long duration, distance;  // Duration used to calculate distance

// ============================= SETUP ===============================
void setup() {
// on initialise la communication
Serial.begin (9600);

// on définit l'ta des pins de l'arduino
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(LEDPinrouge, OUTPUT);
pinMode(LEDPinvert, OUTPUT);

// on éteint toutes les ledPin
digitalWrite(LEDPinrouge, LOW);
digitalWrite(LEDPinvert, LOW);
} // fin du setup

void loop() {
/* The following trigPin/echoPin cycle is used to determine the
distance of the nearest object by bouncing soundwaves off of it. */
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);

digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

//Calculate the distance (in cm) based on the speed of sound.
//distance = duration/57;
distance = duration/57; // testé avec 58, il manque alors 1 cm

if (distance <= maxdist) {


digitalWrite(LEDPinrouge, HIGH);  // Turn LEDPinrouge ON  to indicate "2-10 cm"
digitalWrite(LEDPinvert, LOW);   // Turn LEDPinvert OFF  to indicate ">10 cm"

Serial.print("zone de contact à : ");  // on s'est rapproché trop près du capteur
Serial.print(distance);
Serial.println(" cm ");

}
else {
// si la distance est > à 10 cm et < à 4 m  (non testée)
digitalWrite(LEDPinrouge, LOW); // Turn LEDPinrouge OFF  to indicate "2-10 cm"
digitalWrite(LEDPinvert, HIGH); // Turn LEDPinvert ON  to indicate ">10 cm"

Serial.print("La distance est de : "); // on s'est éloigné du capteur
Serial.print(distance);
Serial.println(" cm ");

}
//Delay 1s before next reading.
delay(1000);
}

/* Utilisation du module breakout RTC_DS1307
Version 1 : à retravailler pour la synchronisation

matériel :
1 led rouge pour visualiser l'allumage et l'extinction d'une led

Branchements du breakout RTC DS1307:
Gnd --> GND
Vcc --> 5 V
Sda --> analog pin A4
Scl --> analog pin A5

*/

// ne pas oublier les library
#include <Arduino.h>
#include <Wire.h>
// Penser à créer 1 sous repertoire RTClib dans le répertoire lib, y placer
// RTClib.h et RTC.cpp
#include "RTClib.h"

// on déclare les pins utilisés sur l'arduino
int PIN_LED = 8;

// on déclare les objets
RTC_DS1307 rtc;    // Create a RealTimeClock object
bool alarmTriggered = false;

// ======================== SETUP =============================
void setup()
{
Serial.begin(9600); // Set up for Serial Monitor to be able to see this work
// Set this in the lower right of the Serial Monitor screen

Serial.println("YourDuino.com DS1307 Real Time Clock - Set / Run Utility");

/*----( These lines allow code to work also on Arduino DUE )----- */
#ifdef AVR
Wire.begin();
#else
Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif

rtc.begin(); // Start the RTC library code
if(!rtc.isrunning()) {  // si il n'y a pas de communication avec le module RTC alors ....
Serial.println("RTC ne fonctionne pas !");
/*----( SET the date and time.  Comment OUT these lines after setting )----*/
// Put these "//" in front of the line you do NOT want to use
// following line sets the RTC to the date & time this sketch was compiled
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
// This line sets the RTC with an explicit date & time, for example to set
// May 21, 2015 at 6pm you would call: (use 24 hour time)
//    rtc.adjust(DateTime(2015, 5, 21, 18, 0, 0));
} else {
Serial.println("RTC fonctionne!");
}

pinMode(PIN_LED, OUTPUT);
digitalWrite(PIN_LED, LOW);



}// fin du setup


void loop()
{
DateTime now = rtc.now();  // Read data from the RTC Chip

Serial.print(now.year(), DEC); //
Serial.print('/');
Serial.print(now.month(), DEC);
Serial.print('/');
Serial.print(now.day(), DEC);
Serial.print(' ');
Serial.print(now.hour(), DEC);
Serial.print(':');
Serial.print(now.minute(), DEC);
Serial.print(':');
Serial.print(now.second(), DEC);
Serial.println();

if (now.hour() == 14 && now.minute() == 14 && !alarmTriggered) {
Serial.println("start alarm"); //

alarmTriggered = true;
digitalWrite(PIN_LED, HIGH);
}

if (now.hour() == 14 && now.minute() == 15 && alarmTriggered) {
Serial.println("stop alarm"); //

alarmTriggered = false;
digitalWrite(PIN_LED, LOW);
}


delay(3000);

}// fin du loop

/* Utilisation du capteur de luminosité
matériel : 1 resistance de 10ko pour la photoresistance
*/
/* Photocell simple testing sketch.
Connect one end of the photocell to 5V, the other end to Analog 0.
 Then connect one end of a 10K resistor from Analog 0 to ground
For more information see http://learn.adafruit.com/photocells */


/* stockage des données dans la Micro-SD Breakout Board+
Pour utiliser avec un Arduino ,
connectez GND à la masse, 5V au 5V,
CLK à la pin 13, DO à la ﻿pin 12, DI à la ﻿pin 11, et CS à la ﻿pin 10
- utilisation du mode de stockage : SPI mode
- For the Arduino library we'll be discussing, and nearly every other SD library, the card must be formatted FAT16 or FAT32
aller à : https://learn.adafruit.com/adafruit-micro-sd-breakout-board-card-tutorial/format
*/
#include <Arduino.h>

int photocellPin = 0; // the cell and 10K pulldown are connected to a0
int photocellReading; // the analog reading from the analog resistor divider

void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);
}

void loop(void) {
  photocellReading = analogRead(photocellPin);
  Serial.print("Analog reading = ");
  Serial.print(photocellReading); // the raw analog reading
  // We'll have a few threshholds, qualitatively determined
  if (photocellReading < 10) {
    Serial.println(" - Noir");
  } else if (photocellReading < 200) {
    Serial.println(" - Sombre");
  } else if (photocellReading < 500) {
    Serial.println(" - Lumiere");
  } else if (photocellReading < 800) {
    Serial.println(" - Lumineux");
  } else {
    Serial.println(" - Tres lumineux");
  }
  delay(2000);
}

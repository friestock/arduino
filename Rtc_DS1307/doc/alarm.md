# Bonus : une alarme

Au début de cet article, je vous ai parlé de la possibilité de déclencher des évènements à partir de l’horloge. Par exemple, je peux vouloir que tous mes volets se ferment à 19h00 et s’ouvre à 7h00, ou alors que chaque jeudi à 19h57 une alarme retentisse pour me rappeler se sortir les poubelles ! Les possibilités sont vastes. Voyons comment générer une alarme tous les jeudis à 19h57.

```c
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;

void setup () {
  Serial.begin(57600); //Démarrage de la communication
  Wire.begin(); //Démarrage de la librairie wire.h
  RTC.begin(); //Démarrage de la librairie RTClib.h

  //Si RTC ne fonctionne pas
  if (! RTC.isrunning()) {
    Serial.println("RTC ne fonctionne pas !");

    //Met à l'heure à date à laquelle le sketch est compilé
    //RTC.adjust(DateTime(__DATE__, __TIME__));
    }
  }

void loop() {
  //Heure actuel
  DateTime now = RTC.now();

  //Alarme se déclenchant le jeudi à 19h57
  if(now.dayOfTheWeek() == 4 && now.hour() == 19 && now.minute() == 57) {   
    //Day of week : 1 pour lundi, 2 pour mardi, ...
    Serial.println("Declenchement de l'alarme");
  //Pas d'alarme
  } else {
    Serial.println("Pas d'alarme");

  }

  delay(1000);
}


```

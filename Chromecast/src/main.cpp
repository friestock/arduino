/* Déclencher une video de youtube à l'aide d'une chromecast reliée à un
shield Ethernet. Le tout sur une Arduino uno

matériel :
- une chromecast video
- un shield internet
- un capteur PIR (cable rouge =+5v, cable noir =Gnd, cable jaune au Pin digital =2)
- une led (+ au Pin_digital=9, - au GND) et resistance comme témoin de visualisation
- un cable reseau RJ45
- une box + reseau

à définir :
- Ip de la shield Ethernet
- Ip de la ChromeCast

Penser à créer les 2 repertoires pour les lib
- WebSocketClient
- WebSocketServer , en fait pas sur que cela serve dans ce cas ici

  ChromeCast client

 This sketch connects to a ChromeCast device and loads a YouTube video.
 This sketch requires an Arduino Ethernet shield.

 To customize this sketch for your own YouTube video:
 1. Determine the IP address of your ChromeCast device and change the chromecast variable value in the sketch.
 2. Get the YouTube ID from the web site. It will be the URL parameter value after "v" (e.g. for http://www.youtube.com/watch?v=GWXLPu8Ky9k, v is "GWXLPu8Ky9k").
 3. Put the YouTube ID in the youtube variable value.

voir aussi
https://bitbucket.org/ThomasKowalski/pcremote-pc-server

 */
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

/*Enter a MAC address for your ethernet shield (or keep the default value).
 Newer Ethernet shields have a MAC address printed on a sticker on the shield.
*/
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// TODO Enter your ChromeCast device IP address:
// pour cela afficher sur la tablette ou telephone :
// la configuration de la isachromecast
// taper dans la fenetre : https://www.google.com/chromecast/setup/
// installer si nécessaire l'application de google store ,
// puis regarder en bas à gauche l'adresse ip et l'adresse MAC
// isachromecast est à l'adresse ip 192,168,1,11
// Attention virgule et non point !!!
IPAddress chromecast(192,168,1,12);
// MAC: 6C:AD:F8:85:E5:D3       pas utile !

// TODO Change v parameter value to your YouTube video ID:
// ci-dessous lancement d'une playlist
char youtube[] = "v=RbUMKenn5l8" ;
/*
"v=icgGyR3iusU&list=RDicgGyR3iusU" ; //?start=60&end=120";

ci-dessous qq videos :
"v=RbUMKenn5l8" // london grammar 4m40
"v=pkeDBwsIaZw"  // London grammar 3mn30
"v=GWXLPu8Ky9k"; // = alarme debute à t=0
"v=GWXLPu8Ky9k#t=1m15s" ; // alarme debute à 1mn 1m15s
"v=9ZpfEOEh08w";
"v=xWtfo9kuRTU";  // de la musique 1h
"v=9ZpfEOEh08w" // rechercher l'ip de la chromecast
// ?start=60&end=120


http://10.x.x.x:8008/apps/Netflix
http://10.x.x.x:8008/apps/YouTube
http://10.x.x.x:8008/apps/GoogleMusic
http://10.x.x.x:8008/apps/ChromeCast
http://10.x.x.x:8008/apps/Pandora
*/

////////////////////////////////////////////////////////
// You shouldn't have to change anything below this line.



// PIR sensor: http://www.ladyada.net/learn/sensors/pir.html

int ledPin = 9;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;
// pas encore fait
// int pinBouton = 7;              // bouton pour eteindre l'alarme

// Track if youtube video was loaded once
int done = 0;

// Ethernet library
EthernetClient client;

// Start of the sketch
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input



  // Open serial communications (pour visualisation à la console)
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for the serial port to open
  }

  // Start the ethernet connection
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to get an IP address using DHCP");
    // Do nothing forever
    for(;;)
      ;
  }

  Serial.print("Arduino IP address: ");
  Serial.println(Ethernet.localIP());

  // Wait for the ethernet shield to initialize
  delay(1000);

  // Flash the LED to show ethernet is ready
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
}

// Keep running the sketch
void loop()
{
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    if (pirState == LOW) {
      digitalWrite(ledPin, HIGH);  // turn LED ON
      // We have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;



    if (done==0) {
        //done = 1;   // just do it once (à supprimer si on le veut actif 1 fois seulement)
        Serial.println("Connecting to ChromeCast device...");
        // Connect to the ChromeCast web server on port 8008
        if (client.connect(chromecast, 8008)) {
          Serial.println("Connected to ChromeCast device");


          // Make a HTTP POST request to start the ChromeCast YouTube app
          client.println("POST /apps/YouTube HTTP/1.1");
          client.println("Host: www.arduino.cc");
          client.println("User-Agent: arduino-ethernet");
          client.println("Connection: close");
          client.println("Content-Type: application/x-www-form-urlencoded");
          client.print("Content-Length: ");
          client.println(strlen(youtube));
          client.println();
          client.println(youtube);
          client.println();

          client.stop();

          Serial.println("YouTube app started on ChromeCast device");
        }
      }
      else {
        Serial.println("Connection to ChromeCast device failed");
      }
    }
  }
  else {
    if (pirState == HIGH){
      digitalWrite(ledPin, LOW); // turn LED OFF
      // We have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}

/*
22/04/17
Objectif : Afficher la température, la luminosité ainsi que l'état de la pile
alimentant l'arduino. Le tout sur une page web consultable sur le navigateur
à l'adresse donnée

au préalable par le site :http://www.mon-ip.com/
ex : Votre adresse IP est : 90.39.29.88
ouvrir la connection par la livebox en autorisant l'entrée au port de l'arduino
ex : ip 192.168.1.13 ouvert au port 80
Il suffira de taper dans la fenetre du navigateur 90.39.29.88:80 puis entrée

matériel :
- Shield Ethernet
- détecteur de température lm35 Analogpin =A2
- photocellPin = A3
- ledPin =DigitalPin9
- breakout RTC DS1307
- 1 cable RJ45 pour connecter l'arduino à la box
- 1 alimentation autonome ex : pile 9v

NE PAS OUBLIER LES LIBRARY !!
- DS1307
- RTClib

https://forum.arduino.cc/index.php?topic=448946.0
https://forum.arduino.cc/index.php?topic=448946.0
mesurer la tension de son arduino :
https://www.carnetdumaker.net/articles/mesurer-la-tension-dalimentation-dune-carte-arduino-genuino-ou-dun-microcontroleur-avr/

Branchements du breakout RTC DS1307:
Gnd --> GND
Vcc --> 5 V
Sda --> analog pin A4
Scl --> analog pin A5



*/ *****************************************************************************
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>                         // interface I2C pour l'horloge DS1307
/*-----( Import needed libraries )-----*/
#include "RTClib.h"
#include <ds1307.h>

/*Enter a MAC address for your ethernet shield (or keep the default value).
Newer Ethernet shields have a MAC address printed on a sticker on the shield.
*/
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // du shiel si il devient serveur
//byte mac[] = { 0xB8, 0x6B, 0x23, 0xFD, 0x3A, 0xB4 }; //b8:6b:23:fd:3a:b4 mac du portable
IPAddress ip(192,168,1,13);  // ip arduino : 192.168.1.13

int ledPin = 9;                // choose the pin for the LED
const int lm35Pin = A2;        // On définit le port de branchement du LM35 en A2
const int photocellPin = A3;  // the cell-luminosité and 10K pulldown are connected to A1
int photocellReading;         // the analog reading from the analog resistor divider
int val = 0;
float temperature;

/*-----( Declare objects )-----*/
DateTime DateHeure;                     // objet contenant les données temporelles
String ChainesDonneesTemps;            //Objet string pour les données à écrire


ds1307 DS1307;
uint8_t buffer[7]; // receiving buffer

bool alarmTriggered = false;

// Track if youtube video was loaded once
int connected = 0;
int port = 80;

// Ethernet library
EthernetClient client;
EthernetServer server(80);


// Start of the sketch
void setup() {
  // on cherche à mesurer la vitalité de la batterie qui alimente l'arduino
  Serial.println(F("VCC-O-Meter"));

  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(lm35Pin , INPUT);     // declare sensor as input
  pinMode(photocellPin , INPUT);     // declare sensor as input

  // Open serial communications (pour visualisation à la console)
  Serial.begin(9600);
  Serial.println("YourDuino.com DS1307 Real Time Clock - Set / Run Utility");

// ************************ gestion de l'horloge ************************
Wire.begin(); // initialisation de l'interface I2C pour l'horloge DS1307
Serial.println("Real Time Clock module with DS1307 test sketch");
DS1307.resume();   // turn on the internal clock


// *****************************************************************
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
  Serial.println(Ethernet.localIP());   // 192.168.1.13 à charny

  // Wait for the ethernet shield to initialize
  delay(1000);

  // Flash the LED to show ethernet is ready
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
}
// ************* programme de mesure de l'état de la batterie **************
/*
Pour fonctionner, le code ci-dessus (et ci-dessous) a besoin de configurer
la référence de tension à GND puis à VCC. Si une tension est injectée sur
la broche AREF, il y a aura création d'un court-circuit.
Si vous utilisez la broche AREF, n'utilisez pas ce code.
*/

/** Mesure la référence interne à 1.1 volts */
unsigned int analogReadReference(void) {

  /* Elimine toutes charges résiduelles */
  ADMUX = 0x4F;
  delayMicroseconds(5);

  /* Sélectionne la référence interne à 1.1 volts comme point de mesure, avec comme limite haute VCC */
  ADMUX = 0x4E;
  delayMicroseconds(200);

  /* Active le convertisseur analogique -> numérique */
  ADCSRA |= (1 << ADEN);

  /* Lance une conversion analogique -> numérique */
  ADCSRA |= (1 << ADSC);

  /* Attend la fin de la conversion */
  while(ADCSRA & (1 << ADSC));

  /* Récupère le résultat de la conversion */
  return ADCL | (ADCH << 8);
}


// ************************************************************************

void loop() {
  // **************** on teste la batterie *****************************
  /*
   * Idéalement :
   * VCC = 5 volts = 1023
   * Référence interne = 1.1 volts = (1023 * 1.1) / 5 = 225
   *
   * En mesurant la référence à 1.1 volts, on peut déduire la tension d'alimentation
   * réelle du microcontrôleur
   * VCC = (1023 * 1.1) / analogReadReference()
   */
  float tension_alim = (1023 * 1.1) / analogReadReference();
  Serial.print("la tension d'alimentation est de : ");
  Serial.println(tension_alim, 3);

  if ( tension_alim < 5 ) { // si les deux lectures voient une coupure
      digitalWrite(ledPin, HIGH);
      //Serial.println( "Coupure prochaine!");
      delay (500),
      digitalWrite(ledPin, LOW);
  } else {

      //Serial.println( "---------OK----------- !");
      //digitalWrite(ledPin, LOW);
      //delay (500),
}

  delay(1000);

  // *****************  définition du temps *******************************
  DS1307.getDate(buffer);
  /*
  Serial.print("Date(dd:mm:yy) ");
  Serial.print(buffer[4], DEC);    // day
  Serial.print(':');
  Serial.print(buffer[5], DEC);    // month
  Serial.print(':');
  Serial.print(buffer[6], DEC);    // year
  Serial.print(':');
  Serial.print(" Time(hh:mm:ss) ");
  Serial.print(buffer[2], DEC);    // hours
  Serial.print(':');
  Serial.print(buffer[1], DEC);    // minutes
  Serial.print(':');
  Serial.println(buffer[0], DEC);  // seconds
  */
  ChainesDonneesTemps= String (buffer[4], DEC)+'/'+ String(buffer[5], DEC)+'/'
  + String(buffer[6], DEC)+'/'
  + String(buffer[2]+1, DEC)+':' // on ajoute 1h pour l'heure d'été
  + String(buffer[1], DEC)+':'  // une mise à l'heure automatique
  + String(buffer[0], DEC);     // de l'heure n'est pas possible
  Serial.println();


  // ************************ température et luminosité ************************
  temperature = (5.0 * analogRead(lm35Pin) *100.0) / 1024;
  photocellReading = analogRead(photocellPin);
  // ************************ listen for incoming clients **********************
  EthernetClient client = server.available();
  if (client) {
    //  Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();
          client.println("<HTML><HEAD>");
          //client.println("<HEAD>");
          client.println("<meta charset='UTF-8'>");
          client.println("<meta http-equiv='refresh' content='5'>");
          client.println("<TITLE>T°C et Lux</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY><TABLE>");
          //client.println("<TABLE>");
          client.println("<CAPTION><h2> PROGRAMME DE GESTION <br>de <br> température et luminosité</h2></CAPTION>");
          //client.println("</CAPTION>");
          client.println("<br>");
          client.println("<TR><TH width=300> Date<TH>Température </TH><TH> Luminosité </TH><TH width=200> VCC (volts) </TH></TR>");
          //client.println("<br>");

          client.println("<TR> <TH width=300>");
          client.println(ChainesDonneesTemps);
          client.println("</TH> <TH width=200>");
          client.print(temperature);
          client.println("</TH> <TH width=200>");
          client.print(photocellReading);
          client.println("</TH> <TH width=200>");
          client.print(tension_alim);
          client.println("</TH></TR>");

          client.println("</TABLE></HTML>");

        break;
      }

} // fin du if (client.available())
}   // fin while (client.connected())
} // fin du if client

// give the web browser time to receive the data
delay(1);
// close the connection:
client.stop();
//  Serial.println("client disconnected");

}  // fin du loop

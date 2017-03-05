#include <Arduino.h>
//===Module double relais ==========================
//
// Exemple de  clignottement d'une lampe toutes les 3 secondes
// par C ROLLAND 26 09 2013 Tiptopboards.com
//
//==================================================
// Broche 3 en sortie commande du relais n1
const int RELAIS = 3; //declaration broche 3 output

boolean etatRelais = 0; // Etat du relais (on / off)

void setup()   {
  Serial.begin(9600);   //Ouvre le port série à 9600 bauds
  // Broche de sortie
  pinMode(RELAIS, OUTPUT); //Configure la broche RELAIS en sortie
} //  Fin du setup


void loop(){ // Boucle principale

   etatRelais=!etatRelais; // inverse l'état du relais
   digitalWrite(RELAIS,etatRelais); // met la broche de commande dans l'état voulu
   Serial.println(etatRelais); //Affichage dans le serial monitor pour contrôle
   delay (3000); // pause 3 secondes
} // fin de void loop

#include <LiquidCrystal.h> // on importe la bibliothèque
LiquidCrystal lcd(12,11,5,4,3,2); // on crée l'objet écran

void setup() {
  lcd.begin(16,2); //on initialise la communication avec 16 colonnes et deux lignes
  lcd.clear(); // on efface l'écran
  lcd.print("Bonjour,"); // on écrit Bonjour
  lcd.setCursor(0,0); //on passe à la ligne suivante
  lcd.print("je m'apelle raphael"); // on finit d'écrire
}

void loop() {

}

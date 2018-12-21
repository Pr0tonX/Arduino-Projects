#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {

 lcd.begin(16,2);
 lcd.setCursor(0,1);
 lcd.print("  ");
 lcd.setCursor(0,0);
 lcd.print("  Salut les amis GEEK! Je suis un jeune qui cherche a faire marcher mon ecran");

}

void loop() {
  lcd.scrollDisplayLeft();
  delay(500);

}

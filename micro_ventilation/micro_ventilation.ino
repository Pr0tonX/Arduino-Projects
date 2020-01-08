#define micro 0
#define power 5
#define ledOUT 8

#include <FastLED.h>
#define NUM_LEDS 5 // définir le nombre de leds
CRGBArray<NUM_LEDS> leds; 

int charge = 10 ;
uint8_t threshold = 500 ;



void setup() {
  Serial.begin(9600); // ouvrir la connexion série
  pinMode(power, OUTPUT);
  pinMode(micro, INPUT);

  FastLED.addLeds<NEOPIXEL, 8>(leds, NUM_LEDS);
  LEDS.setBrightness(255);
  FastLED.clear();
  
}

void loop() {
  int microValue = analogRead(0); // lire la valeur sur la pin A0 et la stocker dans une variable entière
  //Serial.print("microValue:");
  Serial.println(microValue); // imprimmer le contenu de la variable dans le moniteur série

  if ( microValue > threshold && charge < 10) {
    //Serial.println(charge);
    charge = charge + 1 ;
  } else if ( charge > 0.5 ){
   // Serial.println("prout");
    charge = charge - 1 ;
    
  }
 // Serial.println(charge);
  uint8_t maxleds = int(map(charge, 0, 10, 0, 6));

  /*for (uint8_t i = 0 ; i < maxleds ; i ++){

    //byte byte0 = map(value0, 0, 1023, 0, 255); // scale the value of first potentiometer
    //byte byte1 = map(value1, 0, 1023, 0, 255); // scale the value of second potentiometer
    //byte byte2 = map(value2, 0, 1023, 0, 255); // scale the value of third potentiometer
    int gradient = int(map(charge, 0, 10, 0, 255));
  
    leds[i] = CHSV(gradient, 255, 255);
    FastLED.show();
  }

/*  for (uint8_t i = 6 ; i > maxleds ; i --){
    leds[i] = CHSV(0, 0, 0);
    FastLED.show();
  
  }*/

  int sigma = map(charge, 0, 10, 50, 255);
  //Serial.print("sima : ");
   //Serial.println(sigma);
  analogWrite(power, sigma);

  delay(100);
}


#include <string.h> // we'll need this for subString
#define MAX_STRING_LEN 20 // like 3 lines above, change as needed.

#include <Servo.h>

Servo serv1;
Servo serv2;
Servo serv3;

// code nécessaire au fonctionne ment des leds
#include <FastLED.h>
#define NUM_LEDS 6
CRGBArray<NUM_LEDS> leds;

int wait = 300;
int down = 0;
int up = 180;

void setup() {

  serv1.attach(5);
  serv2.attach(6);
  serv3.attach(9);
 
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, 10>(leds, NUM_LEDS);
}

void loop() {
    
  if (Serial.available() > 0) { //makes sure something is ready to be read
    // cette partie de code permet de recomposer le message provenant de processing
    static int bufpos = 0; //starts the buffer back at the first position in the incoming serial.read
    char val = Serial.read(); //assigns one byte (as serial.read()'s only input one byte at a time

    if (val == 'a'){
        notif();
      }
      else if (val == 'z'){
        enter();
      } 
      else if (val == 'e'){

        out();
      } else if (val == 'r'){
        wave_down();
      }
  }
}


void notif(){
  serv1.write(down);
  serv2.write(down);
  serv3.write(down);

  delay(wait);
  serv1.write(up);
  serv2.write(up);
  serv3.write(up);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 255);
  }
  FastLED.show(); // on actualise le ruban de led
  
  delay(wait);
  serv1.write(down);
  serv2.write(down);
  serv3.write(down);
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show(); // on actualise le ruban de led
  delay(wait);
  serv1.write(up);
  serv2.write(up);
  serv3.write(up);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 255);
  }
  FastLED.show(); // on actualise le ruban de led
  delay(wait);
  serv1.write(down);
  serv2.write(down);
  serv3.write(down);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show(); // on actualise le ruban de led
}

void enter(){
  serv1.write(down);
  serv2.write(down);
  serv3.write(down);

  delay(wait);
  serv1.write(up);
  serv3.write(up);

  leds[0] = CRGB(0, 0, 255);
  leds[1] = CRGB(0, 0, 255);
  leds[4] = CRGB(0, 0, 255);
  leds[5] = CRGB(0, 0, 255);
  delay(wait);
  serv1.write(down);
  serv2.write(up);
  serv3.write(down);

  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 255);
  leds[3] = CRGB(0, 0, 255);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  
  delay(wait);
  serv1.write(up);
  serv2.write(down);
  serv3.write(up);

  leds[0] = CRGB(0, 0, 255);
  leds[1] = CRGB(0, 0, 255);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 255);
  leds[5] = CRGB(0, 0, 255);
  delay(wait);
  serv1.write(down);
  serv2.write(down);
  serv3.write(down);

  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
}

void out(){
  serv1.write(down);
  serv2.write(down);
  serv3.write(down);

  delay(wait);
  serv2.write(up);
  leds[2] = CRGB(0, 0, 255);
  leds[3] = CRGB(0, 0, 255);
  
  delay(wait);
  serv1.write(up);
  serv3.write(up);
  serv2.write(down);
  leds[0] = CRGB(0, 0, 255);
  leds[1] = CRGB(0, 0, 255);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 255);
  leds[5] = CRGB(0, 0, 255);
  delay(wait);
  serv1.write(down);
  serv2.write(up);
  serv3.write(down);

  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 255);
  leds[3] = CRGB(0, 0, 255);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  delay(wait);
  serv1.write(down);
  serv2.write(down);
  serv3.write(down);

  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
}

void wave_down(){
  serv1.write(down);
  serv2.write(down);
  serv3.write(down);

  delay(wait);
  serv1.write(up);
  leds[0] = CRGB(0, 0, 255);
  leds[1] = CRGB(0, 0, 255);
  delay(wait);
  serv1.write(down);
  serv2.write(up);
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 255);
  leds[3] = CRGB(0, 0, 255);
  delay(wait);
  serv2.write(down);
  serv3.write(up);
  leds[0] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 255);
  leds[5] = CRGB(0, 0, 255);
  delay(wait);
  serv3.write(down);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);

  delay(wait);
  serv1.write(up);
  leds[0] = CRGB(0, 0, 255);
  leds[1] = CRGB(0, 0, 255);
  delay(wait);
  serv1.write(down);
  serv2.write(up);
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 255);
  leds[3] = CRGB(0, 0, 255);
  delay(wait);
  serv2.write(down);
  serv3.write(up);
  leds[0] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 255);
  leds[5] = CRGB(0, 0, 255);
  delay(wait);
  serv3.write(down);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
}

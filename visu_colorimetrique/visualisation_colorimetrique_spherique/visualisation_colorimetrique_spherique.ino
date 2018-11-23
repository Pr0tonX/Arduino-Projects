#include <Wire.h>
#include <ADXL345.h>
#include <FastLED.h>
#define NUM_LEDS 5 
ADXL345 accel;
CRGBArray<NUM_LEDS> leds;
float xColor,yColor,zColor;

void setup() {
  Serial.begin(9600);
  accel.powerOn(); 
  // init strip led on pin 9
  FastLED.addLeds<NEOPIXEL, 9>(leds, NUM_LEDS);
}

void loop() {

//read and store value of accelerometer
  int x, y, z;
  accel.readXYZ(&x, &y, &z);   
    
 /* Serial.print("values of X , Y , Z: ");
  Serial.print(x);
  Serial.print(" , ");
  Serial.print(y);
  Serial.print(" , ");
  Serial.println(z); */
  

  // array to store values from getAcceleration 
  double xyz[3]; 
  accel.getAcceleration(xyz); 

//colors of strip leds
  xColor=map(x,-130,130,0,255);
  yColor=map(y,-130,130,0,255);
  zColor=map(z,-130,130,0,255);

  /*
   Serial.println(xColor);
  Serial.println(yColor);
    Serial.println(zColor);
    Serial.println("-----------------");
    */
  

 /* 
  Serial.print("X=");
  Serial.print(xyz[0]);
  Serial.print(" g , ");
  Serial.print("Y=");
  Serial.print(xyz[1]);
  Serial.print(" g , ");
  Serial.print("Z=");
  Serial.print(xyz[2]);
  Serial.println(" g");
  */

  //new values RGB of leds
for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(xColor,yColor,zColor);
  }
  
  FastLED.show(); //actualize led strip
  
  String json;
  //colors
  json = json + "{\"xColor\": ";
  json = json + xColor;
  json = json + ";\"yColor\": ";
  json = json + yColor;
  json = json+ ";\"zColor\": ";
  json = json + zColor;
  //rotations
  json = json + "{\"x\": ";
  json = json + x;
  json = json + ";\"y\": ";
  json = json + y;
  json = json+ ";\"z\": ";
  json = json + z;
  
  json = json + "}";
  Serial.println(json);

  
  //delay(1000); // if you want to look in the monitor
}

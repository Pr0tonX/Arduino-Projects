/*  Example of a simple light-sensing theremin-like
    instrument with long echoes,
    using Mozzi sonification library.

    Demonstrates ControlDelay() for echoing control values,
    and smoothing an analog input from a sensor
    signal with RollingAverage().

    The circuit:

       Audio output on digital pin 9 on a Uno or similar, or
      DAC/A14 on Teensy 3.0/3.1, or
       check the README or http://sensorium.github.com/Mozzi/

    Light dependent resistor (LDR) and 5.1k resistor on analog pin 1:
       LDR from analog pin to +5V (3.3V on Teensy 3.0/3.1)
       5.1k resistor from analog pin to ground

    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users

    Tim Barrass 2013, CC by-nc-sa.
*/

//#include <ADC.h>  // Teensy 3.0/3.1 uncomment this line and install http://github.com/pedvide/ADC
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <tables/triangle_valve_2048_int8.h>
#include <RollingAverage.h>
#include <ControlDelay.h>
#include <mozzi_midi.h>
#include <mozzi_fixmath.h>

#define INPUT_PIN 0 // analog control input: tone
const char VOL_PIN = 2 ;//analog control input : volume


unsigned int echo_cells_1 = 32;
unsigned int echo_cells_2 = 60;
unsigned int echo_cells_3 = 127;

// oscils to compare bumpy to averaged control input
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin0(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin1(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin2(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin3(SIN2048_DATA);

int pValue ;
byte volume;

#define CONTROL_RATE 64 // powers of 2 please
ControlDelay <256, int> kDelay; // 2seconds

// use: RollingAverage <number_type, how_many_to_average> myThing
RollingAverage <int, 32> kAverage; // how_many_to_average has to be power of 2
int averaged;


void setup() {
 // Serial.begin(115200);// set up the Serial output so we can look at the piezo values // set up the Serial output so we can look at the analog levels
  kDelay.set(echo_cells_1);

  startMozzi(CONTROL_RATE);
}

void updateControl() {
  ////////////////// VOLUME ///////////////////////////////
  pValue = mozziAnalogRead(VOL_PIN); // value is 0-600 ~
 //Serial.print("value : ");
 //Serial.println( pValue);

  // map it to an 8 bit volume range for efficient calculations in updateAudio
  //volume = map (pValue, 0, 1023, 255, 0);  // 10 bits (0->1023) shifted right by 2 bits to give 8 bits (0->255) 
  volume =255 -(pValue >>2);
/*  if (volume > 100) volume = 100;
  if (volume < 0)volume = 0; */
//  Serial.print("volume = ");
  //Serial.println(volume);
  
  ////////////////////////// TONE //////////////////////

  int bumpy_input = mozziAnalogRead(INPUT_PIN);
  averaged = kAverage.next(bumpy_input);
  aSin0.setFreq(averaged);
  aSin1.setFreq(kDelay.next(averaged));
  aSin2.setFreq(kDelay.read(echo_cells_2));
  aSin3.setFreq(kDelay.read(echo_cells_3));
}

int updateAudio() {
  return ((int)((
    (((int)aSin0.next()) + 
    ((aSin1.next()) + 
    (((aSin2.next() >> 1))) + 
    (((aSin3.next() >> 2))) 
    )>> 3) *volume ) >>8)) ;
}


void loop() {
  audioHook();
}

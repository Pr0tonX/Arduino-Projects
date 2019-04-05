/*  Example of amplitude modulation (as tremelo),
    using Mozzi sonification library.
  
    Demonstrates audio and control rate updates.
    The tremelo oscillator is updated at control rate,
    and a Line is used to interpolate the control updates
    at audio rate, to remove zipper noise.
    A bit contrived and probably less efficient than just 
    using an audio-rate tremelo oscillator, but hey it's a demo!
  
    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or 
    check the README or https://sensorium.github.com/Mozzi/
  
    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users
  
    Tim Barrass 2012, CC by-nc-sa.
*/

//#include <ADC.h>  // Teensy 3.1 uncomment this line and install https://github.com/pedvide/ADC
#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/triangle_valve_2048_int8.h>
#include <tables/sin2048_int8.h>
#include <Line.h>
#include <mozzi_midi.h>

#define CONTROL_RATE 64 // powers of 2 please

// audio oscillator
Oscil<TRIANGLE_VALVE_2048_NUM_CELLS, AUDIO_RATE> aSig(TRIANGLE_VALVE_2048_DATA);
// control oscillator for tremelo
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> kTremelo(SIN2048_DATA);
// a line to interpolate control tremolo at audio rate
Line <unsigned int> aGain;

#define input 0

void setup(){
    Serial.begin(115200);
  aSig.setFreq(mtof(65.f));
  kTremelo.setFreq(5.5f);
  startMozzi(CONTROL_RATE);
}


void updateControl(){
  // gain shifted up to give enough range for line's internal steps
  int in = mozziAnalogRead(input);
  Serial.println(in);
   unsigned int gain = in << 4 ;
   aGain.set(gain, AUDIO_RATE / CONTROL_RATE); // divide of literals should get optimised away
}


int updateAudio(){
  // cast to long before multiply to give room for intermediate result, 
  // and also before shift,
  // to give consistent results for both 8 and 32 bit processors.
  return (int)((long)((long) aSig.next() * aGain.next()) >> 16); // shifted back to audio range after multiply
}


void loop(){
  audioHook();
}

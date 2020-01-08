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
//#include <util/atomic.h>
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <tables/cos8192_int8.h>
#include <tables/triangle_valve_2048_int8.h>
#include <RollingAverage.h>
#include <ControlDelay.h>
#include <mozzi_midi.h>
#include <mozzi_fixmath.h>
//#include <util/atomic.h>

#define note_PIN 0 // analog control input: tone
const char pulse_PIN = 2 ;//analog control input : volume
char v0;

unsigned int echo_cells_1 = 32;
unsigned int echo_cells_2 = 60;
unsigned int echo_cells_3 = 127;

// oscils to compare bumpy to averaged control input
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin0(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin1(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin2(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin3(SIN2048_DATA);

Oscil<COS8192_NUM_CELLS, CONTROL_RATE> kVol0(COS8192_DATA);
Oscil<COS8192_NUM_CELLS, AUDIO_RATE> aCos0(COS8192_DATA);
int pValue ;
byte volume;

#define CONTROL_RATE 64 // powers of 2 please
ControlDelay <256, int> kDelay; // 2seconds

// use: RollingAverage <number_type, how_many_to_average> myThing
RollingAverage <int, 32> kAverage; // how_many_to_average has to be power of 2
int averaged;

#define NUM_VOICES 8
#define THRESHOLD 10
// notes to play depending on whether note reading increases or decreases
float upnotes[NUM_VOICES] = {
  mtof(62.f), mtof(64.f), mtof(70.f), mtof(72.f), mtof(79.f), mtof(81.f), mtof(86.f), mtof(88.f)
};

float downnotes[NUM_VOICES] = {
  mtof(64.f), mtof(65.f), mtof(88.f), mtof(72.f), mtof(79.f), mtof(84.f), mtof(86.f), mtof(89.f)
};



void setup() {
  // Serial.begin(115200);// set up the Serial output so we can look at the piezo values // set up the Serial output so we can look at the analog levels
  kDelay.set(echo_cells_1);
 // Serial.begin(9600);
  startMozzi(CONTROL_RATE);
}

// returns freq
int noteToFreq(char oscil_num, int note) {
  static int previous_note;
  int freq;
  if (note > previous_note) {
    freq = upnotes[oscil_num];
  } else {
    freq = downnotes[oscil_num];
  }
  previous_note = note;
  return freq;
}


void updateControl() {
  static float previous_pulse_freq;

  ////////////////// PULSE ///////////////////////////////
  int pulse = mozziAnalogRead(pulse_PIN); // value is 0-600 ~
  int note = mozziAnalogRead(note_PIN);
 // Serial.print(pulse);
 // Serial.print("         ");
 // Serial.println(note);



  // map pulse reading to volume pulse frequency
  float pulse_freq = ((float)pulse / 256);
  //Serial.print(pulse, "    ");
  //Serial.println(pulse_freq);
  previous_pulse_freq = pulse_freq;
  kVol0.setFreq(pulse_freq);
  // aCos0.setFreq(noteToFreq(0,note));

  v0 = kVol0.next();
  //Serial.println(v0);

  ////////////////////////// TONE //////////////////////

  averaged = kAverage.next(note);
  aSin0.setFreq(averaged);
  aSin1.setFreq(kDelay.next(averaged));
  aSin2.setFreq(kDelay.read(echo_cells_2));
  aSin3.setFreq(kDelay.read(echo_cells_3));
}

int updateAudio() {
  return v0 / 8 * ((int)aSin0.next() + aSin1.next() + (aSin2.next() >> 1)
                    + (aSin3.next() >> 2)) >> 5;
}


void loop() {
  audioHook();
}

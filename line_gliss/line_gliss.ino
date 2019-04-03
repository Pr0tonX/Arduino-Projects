
//#include <ADC.h>  // Teensy 3.1 uncomment this line and install https://github.com/pedvide/ADC
#include <MozziGuts.h>
#include <Line.h> // for smooth transitions
#include <Oscil.h> // oscillator template
#include <tables/triangle_warm8192_int8.h> // triangle table for oscillator
#include <mozzi_midi.h>

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <TRIANGLE_WARM8192_NUM_CELLS, AUDIO_RATE> aTriangle(TRIANGLE_WARM8192_DATA);

// use: Line <type> lineName
Line <long> aGliss;

#define CONTROL_RATE 64 // powers of 2 please

byte lo_note = 24; // midi note numbers
byte hi_note = 36;

long audio_steps_per_gliss = AUDIO_RATE / 4; // ie. 4 glisses per second
long control_steps_per_gliss = CONTROL_RATE / 4;

// stuff for changing starting positions, probably just confusing really
int counter = 0;
byte gliss_offset = 0;
byte gliss_offset_step = 2;
byte  gliss_offset_max = 36;


void setup(){
  startMozzi(CONTROL_RATE);
}


void loop(){
  audioHook();
}


void updateControl(){
  if (--counter <= 0){
    
    // start at a new note
    gliss_offset += gliss_offset_step;
    if(gliss_offset >= gliss_offset_max) gliss_offset=0;
    
    // only need to calculate frequencies once each control update
    int start_freq = mtof(lo_note+gliss_offset);
    int end_freq = mtof(hi_note+gliss_offset);
    
    // find the phase increments (step sizes) through the audio table for those freqs
    // they are big ugly numbers which the oscillator understands but you don't really want to know
    long gliss_start = aTriangle.phaseIncFromFreq(start_freq);
    long gliss_end = aTriangle.phaseIncFromFreq(end_freq);
    
    // set the audio rate line to transition between the different step sizes
    aGliss.set(gliss_start, gliss_end, audio_steps_per_gliss);
    
    counter = control_steps_per_gliss;
  }
}


int updateAudio(){
  aTriangle.setPhaseInc(aGliss.next());
  return aTriangle.next();
}

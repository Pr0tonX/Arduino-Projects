#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <tables/saw2048_int8.h>
#include <RollingAverage.h>
#include <ControlDelay.h>


#define INPUT_PIN 0 // analog control input
#define fun_PIN 2 // function control

// more time to stand out 
unsigned int echo_cells_1 = 60;
unsigned int echo_cells_2 = 90;
unsigned int echo_cells_3 = 120;

#define CONTROL_RATE 64
ControlDelay <128, int> kDelay; // 2seconds



// oscils to compare bumpy to averaged control input
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin0(SIN2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSin1(SAW2048_DATA); // play different table
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSin2(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> aSin3(SAW2048_DATA);

// use: RollingAverage <number_type, how_many_to_average> myThing
RollingAverage <int, 32> kAverage; // how_many_to_average has to be power of 2
int averaged;
RollingAverage <int, 16> fAverage; // how_many_to_average has to be power of 2
int averagedf; //average the fun pin 

void setup(){
  kDelay.set(echo_cells_1);
  startMozzi();

}


void updateControl(){
  int function = mozziAnalogRead(fun_PIN);
  averagedf = fAverage.next(function);

  
  int bumpy_input = mozziAnalogRead(INPUT_PIN);
  averaged = kAverage.next(bumpy_input);
  aSin0.setFreq(averaged);
  aSin1.setFreq(kDelay.next(averaged));
  aSin2.setFreq(kDelay.read(echo_cells_2));
  aSin3.setFreq(kDelay.read(echo_cells_3));
}


int updateAudio(){
  if ( averagedf < 220){
    return ((int)aSin0.next()); //just one wave, *** does not clear the other echo tables
  }
  else{   //all waves
    return 3*((int)aSin0.next()+aSin1.next()+(aSin2.next()>>1)
    +(aSin3.next()>>2)) >>3;
  }
  }


void loop(){
  audioHook();
}

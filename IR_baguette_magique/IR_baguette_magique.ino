/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

#define l1 7
#define l2 8

int RECV_PIN = 2;
long play1 = 3687369586 ; 
long play2 = 848397 ; 
long play3 = 3119464688 ; 

long pause1 = 556773965 ;
long pause2 = 3977140024 ;
long pause3 = 3977140024;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");

  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume(); // Receive the next value

    if (results.value == play1 || results.value == play2 || results.value == play3){
      Serial.println("play");
      Serial.println(results.value);
      if (digitalRead(l1) == LOW){
        digitalWrite(l1, HIGH);
      } else {
        digitalWrite(l1, LOW);
      }
    }

    if (results.value == pause1 || results.value == pause2 || results.value == pause3){
      Serial.println("pause");
      Serial.println(results.value);
      if (digitalRead(l2) == LOW){
        digitalWrite(l2, HIGH);
      } else {
        digitalWrite(l2, LOW);
      }
    }
    
  }
  delay(100);
}

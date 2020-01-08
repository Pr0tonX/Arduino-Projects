#include <Servo.h> 

// PUMP PINS
#define ENA 5
#define IN1 2
#define IN2 4

//DRONE SERVO
#define ENB 6
#define IN3 7
#define IN4 8

// WATER TUBE SERVO PINS
#define stopservo_left 9
#define stopservo_right 10
#define aqueducPIN 11

Servo aqueduc;

uint8_t stoptheservo = 92 ;

int timestamp ; 
uint16_t t_dronemove = 4000 ;
uint16_t t_pump = 5000 ;
uint16_t t_mv_aqueduc = 1020 ;
uint32_t t_dronepark = ( (2 * t_mv_aqueduc) + t_pump) * 2 ;


void setup() { 
  Serial.begin(9600);
  pinMode(stopservo_left, INPUT);
  pinMode(stopservo_right, INPUT);
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  timestamp = 0 ;
  
  aqueduc.attach(aqueducPIN);

  //move until stop by one side, to recenter
  while (digitalRead(stopservo_left) == 0){
    Serial.println("the aqueduc is moving left to recenter");
    aqueduc.write(100);
  }  

  aqueduc.write(60);
  delay(t_mv_aqueduc);
  aqueduc.write(92);

  Serial.println("aqueduc centered ! ");

} 

void loop() {

   d_move();
   d_stop();
   a_mvLeft();

   p_rotateNormal();
   p_stop(); //p_rotateInversed();
   a_mvRight();

   p_rotateNormal();
   p_stop(); //p_rotateInversed();
   a_center();
} 

// UP/DOWN SERVO

void d_move(){
  Serial.println("the drone is moving");
  delay(t_dronemove);
}
void d_up(){
   analogWrite(ENA, 255);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("the drone is moving");
  delay(t_dronemove);
}

void d_down(){
    analogWrite(ENA, 255);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("the drone is moving");
  delay(t_dronemove);
}


void d_stop(){
  analogWrite(ENA, 255);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("the drone is stopped");
  delay(300);
}


//AQUEDUC
void a_mvLeft(){
  while (digitalRead(stopservo_left) == 0){
    Serial.println("the aqueduc is moving left");
    aqueduc.write(120);
  }  
  aqueduc.write(92);
  delay(300);
}

void a_mvRight(){
  while (digitalRead(stopservo_left) == 0){
    Serial.println("the aqueduc is moving right");
    aqueduc.write(50);
  }  
  aqueduc.write(92);
  delay(300);
}

void a_wait(){
  aqueduc.write(92);
  delay(300);
}

void a_center(){
  aqueduc.write(108);
  delay(t_mv_aqueduc);
  aqueduc.write(92);
  delay(300);
}


// PUMP 
void p_rotateNormal (){
  analogWrite(ENA, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  Serial.println("the pump is pumping");
   delay(t_pump);
}

void p_rotateInversed (){
  analogWrite(ENA, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
   Serial.println("the pump is pumping inverse");
   delay(t_pump);
}

void p_stop() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  Serial.println("the pump is stopped");
  delay(300);
}

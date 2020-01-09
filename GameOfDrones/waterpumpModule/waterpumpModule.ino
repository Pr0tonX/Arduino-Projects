#include <Servo.h> 

// ARM PINS
#define ENA 5
#define IN1 2
#define IN2 4

//DRONE SERVO
#define drPIN 6

// WATER TUBE SERVO PINS
#define stopservo_left 13
#define stopservo_right 12
#define aqueducPIN 11

Servo aqueduc;
Servo drone ;

uint8_t stoptheservo = 92 ;

int timestamp ; 
uint16_t t_dronemove = 2000 ;
uint16_t t_mv_aqueduc = 3000 ;
uint16_t t_pump = 5000 ;

void setup() { 
  Serial.begin(9600);
  pinMode(stopservo_left, INPUT);
  pinMode(stopservo_right, INPUT);
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(drPIN,OUTPUT);

  timestamp = 0 ;
  
  aqueduc.attach(aqueducPIN);
  drone.attach(drPIN);

  //move until stop by one side, to recenter
  while (digitalRead(stopservo_left) == 0){
    Serial.println("the aqueduc is moving right to recenter");
    aqueduc.write(80);
  }  

  aqueduc.write(100);
  delay(t_mv_aqueduc);
  aqueduc.write(92);

  Serial.println("aqueduc centered ! ");

} 

void loop() {

   d_down();

   Serial.println("going to move left");
   
   a_mvLeft();
   p_rotateNormal();
   p_stop(); //p_rotateInversed();
   Serial.println("going to move right");
   a_mvRight();
   p_rotateNormal();
   p_stop(); //p_rotateInversed();
   
   a_center();

   d_up();
   delay(5000);
} 

// UP/DOWN SERVO

void d_move(){
  Serial.println("the drone is moving");
  delay(t_dronemove);
}
void d_up(){
  //drone.write(30);
Serial.println("the drone is moving up");
  delay(t_dronemove);
  drone.write(92);
  delay(300);
}

void d_down(){
 // drone.write(150);
  Serial.println("the drone is moving down");
  delay(t_dronemove);
  drone.write(92);
  delay(300);
}

//aqueduc
void a_mvLeft(){
  while (digitalRead(stopservo_right) == 1){
    Serial.print("the aqueduc is moving left : ");
        Serial.print(digitalRead(stopservo_left));
        Serial.print("  ");
    Serial.println(digitalRead(stopservo_right));
    aqueduc.write(100);
  }  
  aqueduc.write(92);
  delay(300);
}

void a_mvRight(){
  while (digitalRead(stopservo_left) == 0 ){
    Serial.print("the aqueduc is moving right : ");
    Serial.print(digitalRead(stopservo_left));
    Serial.print("  ");
    Serial.println(digitalRead(stopservo_right));
    aqueduc.write(80);
  }  
  aqueduc.write(92);
  delay(300);
}



void a_center(){
  aqueduc.write(100);
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

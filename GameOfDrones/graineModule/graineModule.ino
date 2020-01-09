#include <Servo.h> 
#include <ADXL345.h>

// ARM PINS
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
#define demilunePIN 11

ADXL345 accel;

Servo demilune;

uint8_t stoptheservo = 92 ;

int timestamp ; 
uint16_t t_dronemove = 4000 ;
uint16_t t_arm = 1020 ;
uint8_t angle = 20 ;

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
  
  demilune.attach(demilunePIN);

  //demilune.write(0);

  accel.powerOn();

} 

void loop() {

   d_move();

   int x, y, z;
   accel.readXYZ(&x, &y, &z);

   a_rotateRight();

   dm_rotate();

   a_rotateLeft();

   dm_rotate();

   a_rotateUp();
  
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

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("the drone is stopped");
  delay(300);
}

void d_down(){
    analogWrite(ENA, 255);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("the drone is moving");
  delay(t_dronemove);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("the drone is stopped");
  delay(300);
}


//demilune
void dm_rotate(){
  Serial.println("demilune is moving");
  demilune.write(0);
  delay(500);
  demilune.write(20);
  Serial.println("coming in initial position");
  Serial.println("la graine est en train de tomber");
  delay(1000);
}

//ARM MOVES

void a_rotateRight(){
  Serial.print("arm rotating right : ");
  analogWrite(ENA, 165);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  //delay(100);
  delay(300);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  Serial.println("arm stopped");
}

void a_rotateLeft(){
  Serial.println("arm rotating left");
  analogWrite(ENA, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //delay(250);
  delay(400);
  analogWrite(ENA, 165);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(100);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  Serial.println("arm stopped");
}

void a_rotateUp(){
  Serial.println("arm center up");
  analogWrite(ENA, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  //delay(200);
  delay(500);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  Serial.println("arm stopped");
}

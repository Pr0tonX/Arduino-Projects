#define ENA 5
#define IN1 2
#define IN2 3

void setup() {
  // put your setup code here, to run once:
   pinMode(ENA,OUTPUT);//Configuré en sorties
   pinMode(IN1,OUTPUT);
   pinMode(IN2,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  rotateNormal();
  stopWater();
  rotateInversed();
  stopWater();

  

}

void rotateNormal (){
  analogWrite(ENA, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
   delay(5000);
}

void rotateInversed (){
  analogWrite(ENA, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
   delay(5000);
}

void stopWater() {
  analogWrite(ENA, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
    delay(5000);
}

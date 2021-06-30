import processing.serial.*;

Serial myPort;  

void setup() {
  size(600, 600); 
  colorMode(HSB,255,255,255);
  //initialisation de la bibliothèque série
  println(Serial.list());
  String portName = Serial.list()[0]; //attention à bien utiliser le bon port
  myPort = new Serial(this, portName, 9600);
}

void draw() {

}

void keyPressed(){
  
  myPort.write(key);
  println(key);
}

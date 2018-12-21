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
  int pressed = 0;
  if (mousePressed == true) {    
    pressed = 1;         
  } else {                         
    pressed = 0; 
  }  
  int x =int( map(mouseX, 0, width, 0, 255));
  int y =int( map(mouseY, 0, height, 0, 255));
             
  background(x, y, pressed*255);
             
  String s = pressed + "," + x + "," + y+ ";";
  println(s);
  myPort.write(s);
}

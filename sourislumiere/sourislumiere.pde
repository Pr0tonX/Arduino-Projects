import processing.serial.*;
Serial myPort;

float x;
float y;
void setup(){
  size(900,900);
  background(0);
}

void draw(){
  translate(0,0,0);
x=mouseX;
y=mouseY;
fill(230,20,15);
noStroke();
box(150);

}

//Cube Rotation Demonstration 
 int rotzfacteur = 0; //z rotation factor controlled by up/down arrows
 
void setup() {
  size(900, 800, P3D);
}

void draw() {
  //Calculate rotation angle
  float rotx = (mouseY/360.0)*-2*PI+PI;
  float roty = (mouseX/420.0)*2*PI-PI;
  float rotz = rotzfacteur*PI/36;
  background(0);  
  translate(width/2,height/2, 0); 

  // draw stationary box
  strokeWeight(1);
  stroke(255);
  noFill();
  box(238);                  
  
  // rotate drawing coordinates according to user input variables
  rotateX(rotx);  
  rotateY(roty);  
  rotateZ(rotz);  
 
  // draw the rotating axis lines
  strokeWeight(2);
  stroke(200,0,0);
  line(-200, 0, 200, 0);       
  stroke(0,200,0);
  line(0, 200, 0, -200);       
  stroke(0,65,200);
  line(0, 0, -200, 0, 0, 200); 
  
  strokeWeight(1);
  stroke(150,150, 30);
  noFill();
  sphere(140); 
}

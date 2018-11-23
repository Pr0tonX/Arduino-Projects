import processing.serial.*;
Serial myPort;  // Créer un objet serial pour pouvoir lire les information postées sur le port série
float Xrot,Yrot,Zrot;
int rotzfacteur = 0; //z rotation factor controlled by up/down arrows

void setup() {
  size(900, 800, P3D);
  background(0);

  // initialisation de la communication via usb depuis arduino
  // ATTENTION à bien utiliser le port adapté
  printArray(Serial.list()); // imprimmer la liste des appreils connectés au port série
  String portName = Serial.list()[0]; // ma carte arduino est la troisième dans la liste imprimmée dans la console
  myPort = new Serial(this, portName, 9600); // on ouvre la communication
  myPort.bufferUntil('\n');
}

void draw() {
  //stay on center, keep black background & fixed box
  background(0);  
  translate(width/2, height/2, 0); // center drawing start point in screen
  strokeWeight(1);
  stroke(255);
  noFill();
  box(238);    

  //Calculate rotation angles 
  float rotx = (mouseY/360.0)*-2*PI+PI;
  float roty = (mouseX/420.0)*2*PI-PI;
  float rotz = rotzfacteur*PI/36;
  rotateX(rotx);  
  rotateY(roty);  // rotate drawing coordinates according to user input variables
  rotateZ(rotz);  

  // draw the rotating axis lines
  strokeWeight(2);
  stroke(200, 0, 0);
  line(-200, 0, 200, 0);       
  stroke(0, 200, 0);
  line(0, 200, 0, -200);      
  stroke(0, 65, 200);
  line(0, 0, -200, 0, 0, 200); 

  
  strokeWeight(1);
  stroke(150, 150, 30);
  noFill();
  sphere(140);
}

void serialEvent (Serial myPort) {
  try {
    println("serialEvent");
    while (myPort.available() > 0) {
      String inBuffer = myPort.readStringUntil('\n');
      if (inBuffer != null) {
        if (inBuffer.substring(0, 1).equals("{")) {
          JSONObject json = parseJSONObject(inBuffer);
          if (json == null) {
            println("JSONObject could not be parsed");
          } else {
            Xrot=json.getInt("x");
            Yrot=json.getInt("y");
            Zrot=json.getInt("z");
            println(Xrot, "  ", Yrot, "  ", Zrot);
          }
        }
      } else {
      }
    }
  }

  catch (Exception e) {
  }
}

import processing.serial.*;
Serial myPort;  // Créer un objet serial pour pouvoir lire les information postées sur le port série
float R, V, B;
float Xrot,Yrot,Zrot;
int rotzfacteur = 0; //z rotation factor controlled by up/down arrows

void setup() {
  size(900, 800, P3D);
  background(0);

  // initialize communication with Arduinon by USB
  printArray(Serial.list()); // See devices connected to serial ports
  String portName = Serial.list()[0]; // Arduino is the first one in the list (see console)
  myPort = new Serial(this, portName, 9600); // open communication with port
  myPort.bufferUntil('\n');
}

void draw() {
  //stay on center, keep black background & fixed box
  background(0);  
  translate(width/2, height/2, 0); 
 /* 
 strokeWeight(1);
  stroke(255);
  noFill();
  box(238);    
*/

// rotate drawing coordinates according to accelerometer
  rotateX(Xrot);  
  rotateY(Yrot);  
  rotateZ(Zrot);  

  // draw the rotating axis lines
  strokeWeight(3);
  stroke(200, 0, 0);
  line(-300, 0, 300, 0);       
  stroke(0, 200, 0);
  line(0, 300, 0, -300);      
  stroke(0, 65, 200);
  line(0, 0, -300, 0, 0, 300); 

  //the sphere
  strokeWeight(1);
  stroke(R,V,B);
  noFill();
  sphere(140);
}

//for get data from Arduino
void serialEvent (Serial myPort) {
  println("serialEvent");
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

            R=json.getInt("xColor");
            V=json.getInt("yColor");
            B=json.getInt("zColor");
            
            Xrot=map(json.getInt("xColor"),-130,130,0,TWO_PI);
            Yrot=map(json.getInt("xColor"),-130,130,0,TWO_PI);
            Zrot=map(json.getInt("xColor"),-130,130,0,TWO_PI);
            println(R, "  ", V, "  ", B);
          }
        }
      } else {
      }
    }
  }

  catch (Exception e) {
  }
}

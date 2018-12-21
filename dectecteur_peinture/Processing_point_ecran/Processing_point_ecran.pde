import processing.serial.*;
Serial myPort;  // Créer un objet serial pour pouvoir lire les information postées sur le port série

int posX;

void setup(){
  size(1600,800);
  background(0);
    // initialize communication with Arduinon by USB
  printArray(Serial.list()); // See devices connected to serial ports
  String portName = Serial.list()[0]; // Arduino is the first one in the list (see console)
  myPort = new Serial(this, portName, 9600); // open communication with port
  myPort.bufferUntil('\n');
}

void draw(){
  background(0,15);
  noStroke();
  fill(255);
  ellipse(posX,height/2,20,20);
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

            posX = json.getInt("distance");
          }
        }
      } else {
      }
    }
  }

  catch (Exception e) {
  }
}
  

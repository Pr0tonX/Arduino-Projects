#define flex 0

void setup() {
  Serial.begin(9600);
 }

void loop() {

String json;
  json = "{\"flex\":";
  json = json + analogRead(0);
  json = json + "}";

  Serial.println(json);
  
}

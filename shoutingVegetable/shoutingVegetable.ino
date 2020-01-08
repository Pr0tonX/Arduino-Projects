void setup() {
  Serial.begin(9600); // ouvrir la connexion série
  
}

void loop() {
  int value = analogRead(0); // lire la valeur sur la pin A0 et la stocker dans une variable entière
  Serial.println(value); // imprimmer le contenu de la variable dans le moniteur série
}

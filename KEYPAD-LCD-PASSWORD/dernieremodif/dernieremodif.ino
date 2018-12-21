 #include <Keypad.h>
#include <Password.h>


int alarmeOK= 0; //0 alarme non activée, 1=alarme activée, intrus!
int alarmestatut = 0; //0=alarme étieite, 1=alarme allumée
unsigned long t_start=millis();
unsigned long t_end=0;

String newPasswordString; 
char newPassword[4]; //mot de passe avec 4 caractères
Password password = Password( "1748" );
byte maxPasswordLength = 4; 
byte currentPasswordLength = 0;

const byte ROWS = 4; //4 lignes
const byte COLS = 4; //4 colonnes
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
//Brancher le clavier sur 2 3 4 5 (colonnes) et 6 7 8 9 (lignes)
byte rowPins[ROWS] = {9, 8, 7, 6}; //Lignes
byte colPins[COLS] = {5, 4, 3, 2}; //Colonnes
// Connections des touches
/*
S1  contact 4 8
S2  contact 3 8
S3  contact 2 8
S4  contact 1 8
S5  contact 4 7
S6  contact 3 7
S9  contact 4 6
S10  contact 3 6
S11  contact 2 6
S12  contact 1 6
S13  contact 4 5
S14  contact 3 5
S15  contact 2 5
S16  contact  1 5
*/

// Initialiser une instance de la classe keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup(){
  Serial.begin(9600);   //Serial monitor
  Serial.println("Test de clavier 16 touches");

  pinMode(12,INPUT);
  pinMode(13,OUTPUT);
  // Pour activer l'état HOLD
  unsigned int time_hold = 4;
  keypad.setHoldTime(time_hold);
  
  //Anti rebond
  unsigned int time_anti_rebond = 4;  //4 ms
  keypad.setDebounceTime(time_anti_rebond);
    
}

void resetPassword() {
   password.reset(); 
   currentPasswordLength = 0; 
}

void checkPassword() { 
   if (password.evaluate()){ //si le mdp est bon,
      Serial.println(" OK.");
      if(alarmeOK == 0 && alarmestatut == 0){
        alarmestatut = 1;//alarme op
        resetPassword();
        active();
        return;       
      }
      if((alarmeOK == 0 && alarmestatut == 1)){
        resetPassword();
        desactive();
        return;
      }
      if((alarmeOK == 1 && alarmestatut == 1)){
        resetPassword();
        desactive();
        return;
      }
   }
   else {
    Serial.println(" Mauvais mot de passe !");
    resetPassword();
   }
}

void desactive(){ //tout est désactivé
  alarmestatut = 0;
  Serial.println("SYSTEME DESACTIVE");
  alarmeOK = 0;
  resetPassword();
  
}

void processNumberKey(char key) { //vérification du mot de passe
   Serial.println(key);
   currentPasswordLength++;
   password.append(key);
   if (currentPasswordLength == maxPasswordLength) {
      checkPassword();
   } 
}

void active(){//l'alarme est opérationelle(alarmestatut=1)
  Serial.println("SYSTEME ACTIVE");
  if (alarmestatut=1){
      char key = keypad.getKey();

  if (key != NO_KEY){ 
      delay(60); 
      switch (key){
      case '#': checkPassword(); break;
      case '*': resetPassword(); break;
      default: processNumberKey(key);
      }
       //Affiche la touche saisie 
    while((digitalRead(12)==LOW)) {}
      alarmeOK = 1;
    }
  
}//fin active
}


void loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){ 
      delay(60); 
      switch (key){
      case '#': checkPassword(); break;
      case '*': resetPassword(); break;
      default: processNumberKey(key);
      }
       //Affiche la touche saisie
  }
  if (alarmeOK == 1){
    Serial.println("Veuillez entrer le mot de passe.");
    t_start=millis();
    t_end=t_start+7000;
    while (t_start<t_end){
      t_start=millis();
      key=keypad.getKey();
      if (key != NO_KEY){
        switch (key){
        case '#': checkPassword(); break;
        case '*': resetPassword(); break;
        default: processNumberKey(key);
        return; 
         }
      }  
    }//attente de 6sec afin de pouvoir rentrer le code
     intrus();//sinon activation de l'alarme
  }//if alarmOk
}//voidloop


void intrus(){
  Serial.println("Intrus détecté.");
  for (uint32_t i=0; i<30; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(10);
    }
  alarmestatut=1;
  alarmeOK=1;
}


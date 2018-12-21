#include <Keypad.h>
#include <Password.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(22, 24, 26, 28, 30, 32);
int alarmeOK= 0; //0 alarme non activated, 1= alarme activated
int alarmestatut = 0; //0= alarm ofe, 1= alarm on
unsigned long t_start = millis();
unsigned long t_end=0;

//set Password
Password password = Password( "1748" );
byte maxPasswordLength = 4; 
byte currentPasswordLength = 0;

//Set Keypad
const byte ROWS = 4; //4 lignes
const byte COLS = 4; //4 colonnes
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

//Connect keypad on 2 3 4 5 (columns) et 6 7 8 9 (rows / lignes)
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

// Initialize Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  
  lcd.begin(16, 2);   

  pinMode(12,INPUT);
  pinMode(13,OUTPUT);
  pinMode(40,INPUT);
  
  // Pour activer l'état HOLD
  unsigned int time_hold = 4;
  keypad.setHoldTime(time_hold);
  
  //Anti rebond : to avoid double enter of number in the code
  unsigned int time_anti_rebond = 4;  //4 ms
  keypad.setDebounceTime(time_anti_rebond);
}

 
void resetPassword() {
   password.reset(); 
   currentPasswordLength = 0; 
}

void checkPassword() { 
   if (password.evaluate()){ //verify pswd

    //if alarm is off, switch it on
      if(alarmeOK == 0 && alarmestatut == 0){
        alarmestatut = 1; 
        resetPassword();
        delay(50);
        active();
        return;       
      }

      //if alarm is on but non activate, switch it off
      if((alarmeOK == 0 && alarmestatut == 1)){
        resetPassword();
        desactive();
        return;
      }

      //if it is activated, switch if off
      if((alarmeOK == 1 && alarmestatut == 1)){
        resetPassword();
        desactive();
        return;
      }
   }
   else {
    lcd.clear();
    lcd.print(" Mauvais code !"); //wrong password
    resetPassword();
    delay(1000);
    lcd.clear();
   }
}

//l'alarme est opérationelle(alarmestatut=1) ; switch alarm on
void active(){
  lcd.clear();
  lcd.print("SYSTEME ACTIVE");
  delay(1500);
  lcd.clear();
  if (alarmestatut=1){
    digitalWrite(33,HIGH);
  } 
    while((digitalRead(12)==LOW)) {
      alarmeOK = 1;
      resetPassword();  
    }
}//fin active

 // désactive l'alarme ; switch off alarm
void desactive(){
  alarmestatut = 0;
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("SYSTEME");
  lcd.setCursor(3,1);
  lcd.print("DESACTIVE");
  alarmeOK = 0;
  digitalWrite(33,LOW);
  resetPassword();
  delay(1500);
  lcd.clear();  
}

void processNumberKey(char key) {
   lcd.print(key);
   currentPasswordLength++;//augmente de 1 la valeur de la variable ; var wich store the current pswd 
   password.append(key);//ajoute un caractere à la varible password contenant le mdp
   if (currentPasswordLength == maxPasswordLength) {
      checkPassword();      
   } 
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
    //compte à rebours de 7sec avant que l'alarme ne sonne ; timer of 7sec before alarm rings
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
    }//attente de 7sec afin de pouvoir rentrer le code ; you have 7sec to enter the pswd
     intrus();//sinon activation de l'alarme ; else alarm is activated
  }
}//voidloop

//when alarm is activated by movement :
void intrus(){
  lcd.clear();
  lcd.print("INTRUS DETECTE");
  for (uint32_t i=0; i<30; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      lcd.setCursor(0,1);
      lcd.print("Entrez le code"); //display : enter the pswd
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(10); 
    }
    
  alarmestatut=1;
  alarmeOK=1;
  lcd.clear();
}

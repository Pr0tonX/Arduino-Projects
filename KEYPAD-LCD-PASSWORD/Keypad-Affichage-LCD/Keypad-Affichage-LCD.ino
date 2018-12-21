#include <LiquidCrystal.h> // Inclusion de la librairie pour afficheur LCD 
#include <Keypad.h> // inclusion de la librairie pour clavier matriciel 

const byte LIGNES = 4; // 4 lignes
const byte COLONNES = 4; //4 colonnes

// --- constantes des broches ---
const int C4=2; //declaration constante de broche 
const int C3=3; //declaration constante de broche 
const int C2=4; //declaration constante de broche 
const int C1=5; //declaration constante de broche 
const int RS=8; //declaration constante de broche 
const int E=9; //declaration constante de broche 
const int D4=10; //declaration constante de broche 
const int D5=11; //declaration constante de broche 
const int D6=12; //declaration constante de broche 
const int D7=13; //declaration constante de broche 
const int L4=16; //declaration constante de broche  
const int L3=17; //declaration constante de broche 
const int L2=18; //declaration constante de broche 
const int L1=19; //declaration constante de broche 

//--- Définition des touches 
char touches[LIGNES][COLONNES] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// tableaux de lignes et colonnes
byte BrochesLignes[LIGNES] = {L1, L2, L3, L4}; //connexions utilisées pour les broches de lignes du clavier
byte BrochesColonnes[COLONNES] = {C1, C2, C3, C4}; //connexions utilisées pour les broches de colonnes du clavier

char touche; // variable de stockage valeur touche appuyée


// --- Déclaration des objets utiles pour les fonctionnalités utilisées ---
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);// Création d'un objet LiquidCrystal = initialisation LCD en mode 4 bits 
// création d'un objet keypad = initialisation clavier 
Keypad clavier = Keypad( makeKeymap(touches), BrochesLignes, BrochesColonnes, LIGNES, COLONNES );
// les broches de lignes sont automatiquement configurées en ENTREE avec pullup interne activé 
// les broches de colonnes sont automatiquement configurées en SORTIE


//**************** FONCTION SETUP = Code d'initialisation *****
// La fonction setup() est exécutée en premier et 1 seule fois, au démarrage du programme

void setup()   { // debut de la fonction setup()
lcd.begin(20,4); // Initialise le LCD avec 20 colonnes x 4 lignes 

delay(10); // pause rapide pour laisser temps initialisation

// Test du LCD

lcd.print("LCD OK") ; // affiche la chaîne texte - message de test
delay(2000); // pause de 2 secondes

lcd.clear(); // // efface écran et met le curseur en haut à gauche
delay(10); // pour laisser temps effacer écran
// les broches de lignes et d'entrée sont configurées automatiquement lors de l'initialisation du clavier 
// ------- Activation du rappel au + interne des broches en entrée si nécessaire -------  

} 

void loop(){ // debut de la fonction loop()
touche = clavier.getKey(); // lecture de la touche appuyée
if (touche != NO_KEY){ // si une touche a été frappée -- gestion de la touche appuyée 
  if (touche=='#') lcd.clear(); else lcd.print(touche); // efface écran si appui # sinon  affiche touche
  delay(300); 
} // fin gestion de la touche appuyée 

} 
// --- Fin programme ---


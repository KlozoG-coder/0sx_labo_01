// Déclaration des broches
const int potentiometrePin = A1;  
const int boutonPin = 2;       
const int ledPins[] = {8, 9, 10, 11}; 

// Variables
int valeurPotentiometre = 0;  
int valeurMapped = 0;         
bool boutonAppuye = false;    

void setup() {
  // Initialisation des broches
  pinMode(boutonPin, INPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Initialisation de la communication série
  Serial.begin(9600);
}

void loop() {
  // Lecture du potentiomètre
  valeurPotentiometre = analogRead(potentiometrePin);
  valeurMapped = map(valeurPotentiometre, 0, 1023, 0, 20);

  // Contrôle des DELs en fonction de la valeur mappée
  if (valeurMapped <= 5) {  // 0 - 25%
    digitalWrite(ledPins[0], HIGH);  //  1ère DEL allumée
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], LOW);
  } else if (valeurMapped <= 10) {  // 25 - 50%
    digitalWrite(ledPins[0], HIGH);  // Allumage des 2 premières DELs
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], LOW);
  } else if (valeurMapped <= 15) {  // 50 - 75%
    digitalWrite(ledPins[0], HIGH);  // Allumage des 3 premières DELs
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[3], LOW);
  } else {  // 75 - 100%
    digitalWrite(ledPins[0], HIGH);  // Allumage des 4 DELs
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[3], HIGH);
  }

  // Lecture de l'état du bouton
  if (digitalRead(boutonPin) == HIGH) {
    if (!boutonAppuye) {
      boutonAppuye = true;
      afficherBarreProgression(valeurMapped);
    }
  } else {
    boutonAppuye = false;
  }
}

// Fonction pour afficher la barre de progression
void afficherBarreProgression(int valeur) {
  int pourcentage = valeur * 5;  // Convertir en pourcentage 
  Serial.print("[");
  for (int i = 0; i < 20; i++) {
    if (i < valeur) {
      Serial.print("#");  // L'avant-dernier chiffre de mon numero etudiant est pair : j'utilise #
    } else {
      Serial.print(".");
    }
  }
  Serial.print("] ");
  Serial.print(pourcentage);
  Serial.println("%");
}
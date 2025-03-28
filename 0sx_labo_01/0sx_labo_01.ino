// Déclaration des broches
const int potentiometrePin = A1;  // Broche du potentiomètre
const int boutonPin = 2;          // Broche du bouton
const int ledPins[] = {8, 9, 10, 11};  // Broches des DELs

// Variables
int valeurPotentiometre = 0;  // Valeur lue du potentiomètre
int valeurMapped = 0;         // Valeur mappée de 0 à 20
bool boutonAppuye = false;    // État du bouton

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
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], LOW);
  } else if (valeurMapped <= 10) {  // 25 - 50%
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], LOW);
  } else if (valeurMapped <= 15) {  // 50 - 75%
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[3], LOW);
  } else {  // 75 - 100%
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[3], HIGH);
  }

  // Lecture de l'état du bouton
  if (digitalRead(boutonPin) {
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
  int pourcentage = valeur * 5;  // Convertir en pourcentage (0-20 -> 0-100)
  Serial.print("[");
  for (int i = 0; i < 20; i++) {
    if (i < valeur) {
      Serial.print("#");
    } else {
      Serial.print(".");
    }
  }
  Serial.print("] ");
  Serial.print(pourcentage);
  Serial.println("%");
}
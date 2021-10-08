
void setup()
{
  pinMode (13, OUTPUT);     // Motor rechtsrum öffnen
  pinMode (12, OUTPUT);     // Motor linksrum schliessen
  pinMode(7, INPUT);        // Der obere Taster
  pinMode(6, INPUT);        // Der untere Taster

  digitalWrite(13, HIGH); 
  digitalWrite(12, HIGH); 
  digitalWrite(8, HIGH); 

  Serial.begin(9600);
  Serial.println("Programm start");
}

void klappe_runter() {
  digitalWrite(13, LOW);
  while(klappe_position() != 0) {}
  digitalWrite(13, HIGH); 
  delay(50);
}

void klappe_hoch() {
  digitalWrite(12, LOW);
  while(klappe_position() != 1) {}
  digitalWrite(12, HIGH); 
  delay(50);
}

int klappe_position() {
  /*

  Ergebnis:
    1: (Klappe oben)
    0: (Klappe unten)
    2: (Klappe in Bewegung)
  */
  int klappe_status;
  int val_unten = digitalRead(6);
  int val_oben = digitalRead(7);

  if(val_unten == LOW && val_oben == LOW) klappe_status = 0;
  else if(val_unten == HIGH && val_oben == HIGH) klappe_status = 1;
  else klappe_status =  2;

  Serial.println("");
  Serial.print("Pin 6 Status: ");
  Serial.print(digitalRead(6));
  Serial.print(", Pin 7 Status: ");
  Serial.print(digitalRead(7));
  Serial.print(" | Klappe Status: ");
  Serial.print(klappe_status);
  
  return klappe_status;
}

void loop ()
{
  delay(4000);
  klappe_runter();
  delay(4000);
  klappe_hoch();
}

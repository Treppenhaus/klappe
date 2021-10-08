#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};

void setup()
{
  pinMode (13, OUTPUT);     // Motor rechtsrum öffnen
  pinMode (12, OUTPUT);     // Motor linksrum schliessen
  pinMode (8, OUTPUT);     // Pin für 5V output
  pinMode(7, INPUT);        // Der obere Taster
  pinMode(6, INPUT);        // Der untere Taster

  digitalWrite(13, HIGH); 
  digitalWrite(12, HIGH); 
  digitalWrite(8, HIGH); 

  Serial.begin(9600);
  Serial.println("Programm start");


  if (! rtc.begin()) {
    Serial.println("Keine Echtzeituhr gefunden!");
    while (1);
  }
}

void klappe_runter() {
  if(klappe_position() == 0) return;
  
  digitalWrite(13, LOW);
  while(klappe_position() != 0) {}
  digitalWrite(13, HIGH); 
  delay(50);
}

void klappe_hoch() {

  if(klappe_position() == 1) return;
  
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
  else if(val_oben == HIGH) klappe_status = 1;
  else klappe_status =  2;

  Serial.println("");
  Serial.print("Pin 6 Status: ");
  Serial.print(digitalRead(6));
  Serial.print(", Pin 7 Status: ");
  Serial.print(digitalRead(7));
  Serial.print(" | Klappe Status: ");
  Serial.print(klappe_status);
  Serial.print(" | Uhrzeit: ");
  
  print_date();
  
  return klappe_status;
}

void print_date() {
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
}
void loop ()
{
  
  print_date();
  DateTime now = rtc.now();
  if(now.hour() % 2 == 0) {
    klappe_hoch();
  }
  
  else if(now.hour() % 2 == 1) {
    klappe_runter();
  }

  else {
    Serial.println(" - Die Klappe wird nicht verändert. Es wird 5 Sekunden gewartet");
    delay(5000);
  }
  
}

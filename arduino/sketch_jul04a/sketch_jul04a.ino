
void setup()
{
  pinMode (13, OUTPUT);     // Motor rechtsrum öffnen
  pinMode (12, OUTPUT);     // Motor linksrum schliessen
  pinMode(7, INPUT);        // Der obere Taster
  pinMode(6, INPUT);        // der untere Taster



}
void loop ()
{
  digitalWrite(13, HIGH); 
  delay(1000);
  digitalWrite(13, LOW);
  delay(28000);
  digitalWrite(13, HIGH); 
  delay(1000);

  digitalWrite(12, HIGH); 
  delay(1000);  
  digitalWrite(12, LOW);
  delay(28000);
  digitalWrite(12, HIGH); 
  delay(1000);

  digitalWrite(8, HIGH);
}

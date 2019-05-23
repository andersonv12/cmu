void setup() {
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
}

void loop() {
  digitalWrite(D5, HIGH);
  delay(5000);
  digitalWrite(D5, LOW);
  digitalWrite(D6, HIGH);
  delay(1500);
  digitalWrite(D6, LOW);
  digitalWrite(D7, HIGH);
  delay(8000);
  digitalWrite(D7, LOW);
}

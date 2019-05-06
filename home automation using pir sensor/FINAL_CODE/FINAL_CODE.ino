void setup() 
{
  Serial.begin(9600);
  pinMode(P1_4, OUTPUT);
  pinMode(P1_5, OUTPUT);
  pinMode(P2_0, OUTPUT);
}

void loop() 
{
  digitalWrite(P1_4, HIGH);
  digitalWrite(P1_5, HIGH);
  digitalWrite(P2_0, HIGH);
  
  int pin = digitalRead(P2_1);
  Serial.println(pin);
  delay(500);
  
  if (pin == 1)
  {
    digitalWrite(P1_4, LOW);
    digitalWrite(P1_5, LOW);
    digitalWrite(P2_0, LOW);
    delay(7200000);


  }

}

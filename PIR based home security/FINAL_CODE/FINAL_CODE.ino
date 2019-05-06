int pirsensor = 8;
int buzzer = 9;
int pirvalue;

void setup()
{
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
}

void loop()
{

  digitalWrite(buzzer, LOW);
  pirvalue = digitalRead(pirsensor);
  if (pirvalue == HIGH)
  {
    Serial.println("Someone tried to steal something from your home");
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
  }
  delay(3000);

}

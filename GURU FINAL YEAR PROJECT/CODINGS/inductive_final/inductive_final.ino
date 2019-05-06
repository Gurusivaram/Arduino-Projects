int monitoring;
int metalDetection = P2_1;

void setup()

{
  Serial.begin(9600);
}

void loop()

{
  monitoring = analogRead(metalDetection);

  Serial.println(monitoring);
  delay(1000);
}

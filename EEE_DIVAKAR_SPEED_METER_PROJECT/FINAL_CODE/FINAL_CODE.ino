#define sensor 6
int delay1()
{
  //unsigned int long k;
  int i, j;
  unsigned int count = 0;
  for (i = 0; i < 1000; i++)
  {
    for (j = 0; j < 1227; j++)
    {
      if (digitalRead(sensor))
      {
        count++;
        while (digitalRead(sensor));
      }
    }
  }
  return count;
}
void setup()
{
  pinMode(sensor, INPUT);
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
}
void loop()
{
  unsigned int time = 0, RPM = 0;
  time = delay1();
  RPM = (time * 12) / 3;
  Serial.println(RPM);
  delay(5000);
  if (RPM < 250)
  {
    digitalWrite(2, LOW);
    delay(5000);
    digitalWrite(2, HIGH);
  }
  else if (RPM < 500)
  {
    digitalWrite(3, LOW);
    delay(5000);
    digitalWrite(3, HIGH);
  }
  else if (RPM < 750)
  {
    digitalWrite(4, LOW);
    delay(5000);
    digitalWrite(4, HIGH);
  }
  else if (RPM < 1000)
  {
    digitalWrite(5, LOW);
    delay(5000);
    digitalWrite(5, HIGH);
  }
}

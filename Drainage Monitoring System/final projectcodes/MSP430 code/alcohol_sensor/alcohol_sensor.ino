int sensor_pin = 5;
int alcohol_value ;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  alcohol_value = digitalRead(sensor_pin);
  Serial.println(alcohol_value);
  delay(1000);
}

int sensor_pin = 5;
int IR_value ;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  IR_value = digitalRead(sensor_pin);
  Serial.println(IR_value);
  delay(100);
}

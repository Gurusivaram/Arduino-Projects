int sensor_pin = A0;
int output_value ;

void setup()

{
  Serial.begin(9600);
}

void loop()

{
  output_value = analogRead(sensor_pin);
  
  Serial.println(output_value);
  delay(100);
}

#include "internaltempsensor.h"
const int tp = 14;
const int ep = 15;
long d;
void  setup()
{
  Serial.begin(9600);

  pinMode(tp, OUTPUT); //setting digital pin 3 as output for the ultrasonic sensor to trigger
  pinMode(ep, INPUT); //setting digital pin 4 to get the echo output from ultrasonic sensor

}
void loop()
{

  int32_t currentValue = MSPTemp.update();
  Serial.print("Internal temperature of the tank : ");
  printDec(currentValue);
  Serial.println();

  delay(2000);
  digitalWrite(tp, LOW);
  delayMicroseconds(2);

  digitalWrite(tp, HIGH);
  delayMicroseconds(10);

  digitalWrite(tp, LOW);
  d = pulseIn(ep, HIGH);
  delay(100);
  Serial.println(d);
  if (d > 1000 && d < 2000)
  {
    Serial.println("The water is 10%");
    delay(1000);
  }
  if (d > 1000 && d < 2000)
  {
    Serial.println("The water is 20%");
    delay(1000);
  }  if (d > 2000 && d < 3000)
  {
    Serial.println("The water is 30%");
    delay(1000);
  }  if (d > 3000 && d < 4000)
  {
    Serial.println("The water is 40%");
    delay(1000);
  }  if (d > 4000 && d < 5000)
  {
    Serial.println("The water is 50%");
    delay(1000);
  }  if (d > 5000 && d < 6000)
  {
    Serial.println("The water is 60%");
    delay(1000);
  }  if (d > 6000 && d < 7000)
  {
    Serial.println("The water is 70%");
    delay(1000);
  }  if (d > 7000 && d < 8000)
  {
    Serial.println("The water is 80%");
    delay(1000);
  }  if (d > 8000 && d < 9000)
  {
    Serial.println("The water is 90%");
    delay(1000);
  }  if (d > 9000 && d < 10000)
  {
    Serial.println("The water is 100%");
    delay(1000);
  }
}
void printDec(int32_t ui)
{
  if (ui < 0)
  { Serial.print("-");

    Serial.print(ui / 10, DEC);
    Serial.print(".");
    Serial.print(ui % 10, DEC);
  }
}

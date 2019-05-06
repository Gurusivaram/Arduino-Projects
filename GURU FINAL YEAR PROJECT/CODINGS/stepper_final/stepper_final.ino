#include <Stepper.h>

const int stepsPerRevolution = 100;

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);


int enA = 6;
int enB = 7;
void setup()
{
  myStepper.setSpeed(60);
  analogWrite(enA, 255);
  analogWrite(enB, 255);



  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void loop()
{

  myStepper.step(stepsPerRevolution);
  delay(1000);

  myStepper.step(-stepsPerRevolution);
  delay(1000);




}

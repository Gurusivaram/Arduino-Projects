
int motorPin1 = 4;
int motorPin2 = 7;
int enablepin= 3;

void setup() 

{
  pinMode(enablepin, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void loop() 

{
  analogWrite(enablepin, HIGH);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  
}

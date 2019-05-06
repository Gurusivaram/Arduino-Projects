#include <LiquidCrystal.h>
LiquidCrystal lcd1(A0, A1, A2, A3, A4, A5);
LiquidCrystal lcd2(8, 9, 10, 11, 12, 13);
const int trigPin1 = 4;
const int echoPin1 = 5;
long duration1 = 0;

const int trigPin2 = 6;
const int echoPin2 = 7;
long duration2 = 0;
int countin = 0, total = 0;
int count = 0;

void setup()

{
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(9600);

  lcd1.clear();
  lcd1.print("MONITOR SYSTEM");
  lcd1.setCursor(0, 1);
  lcd1.print("IS STRATING...");

  lcd2.clear();
  lcd2.print("MONITOR SYSTEM");
  lcd2.setCursor(0, 1);
  lcd2.print("IS STRATING...");

}

void loop()

{

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  delay(80);

  if (duration1 < 3000)
  {
    countin++;
  }

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  delay(80);
  if (duration2 < 3000)
  {
    count++;
  }

  //Serial.println(duration1);
  //delay(100);
  //Serial.println(duration2);
  // delay(100);

  total = abs(countin - count);

  lcd1.clear();
  lcd1.print("IN COUNT= ");
  lcd1.print(countin);
  lcd1.setCursor(0, 1);
  lcd1.print("TOTAL COUNT=  ");
  lcd1.print(total);
  delay(10);

  lcd2.clear();
  lcd2.print("OUT COUNT= ");
  lcd2.print(count);
  lcd2.setCursor(0, 1);
  lcd2.print("TOTAL COUNT=  ");
  lcd2.print(total);
  delay(10);
}

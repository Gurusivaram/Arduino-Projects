#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
int alcohol = 4;
int alcdata;
int greenled = 6;
int redled = 5;
int buzzer = 7;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(redled, OUTPUT);

  lcd.clear();
  lcd.print("MONITOR SYSTEM");
  lcd.setCursor(0, 1);
  lcd.print("IS STRATING...");
  delay(5000);

}

void loop()
{
  alcdata = digitalRead(alcohol);
  Serial.println(alcdata);

  if (alcdata == LOW)
  {
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenled, LOW);
    digitalWrite(redled, HIGH);
    delay(1000);
    lcd.clear();
    lcd.print("DRIVER IS DRUNK");
    lcd.setCursor(0, 1);
    lcd.print("ENGINE WILL STOP");
    delay(5000);
    digitalWrite(buzzer, HIGH);
    lcd.clear();
    lcd.print("PLEASE TAKE REST");
    lcd.setCursor(0, 1);
    lcd.print("AND MOVE THE CAR");
    delay(1000);
    delay(5000);
    digitalWrite(buzzer, LOW);
    delay(10000);
    digitalWrite(redled, LOW);
    delay(1000);
  }
  digitalWrite(greenled, HIGH);
  delay(1000);

  lcd.clear();
  lcd.print("DRIVER IS NOT");
  lcd.setCursor(0, 1);
  lcd.print("DRUNKEN");
  delay(5000);

  lcd.clear();
  lcd.print("ENGINE CONDITION");
  lcd.setCursor(0, 1);
  lcd.print("IS GOOD");
  delay(5000);

  lcd.clear();
  lcd.print("PLEASE DONT");
  lcd.setCursor(0, 1);
  lcd.print("DRUNK AND DRIVE");
  delay(5000);
}


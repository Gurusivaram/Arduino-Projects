#include <LiquidCrystal.h>
LiquidCrystal lcd(P2_0, P2_1, P2_2, P1_5, P1_4, P1_3);

int eyepin = 12;
int buzzer = 11;
int eye = 1;


void setup()
{
  Serial.begin(9600);

  lcd.begin(16, 2);

  lcd.print("     WELCOME ");
  lcd.setCursor(0, 1);
  lcd.print("    RENUKA P");
  delay(5000);

  lcd.clear();
  lcd.print("SLEEP MONITERING");
  lcd.setCursor(0, 1);
  lcd.print("BOOTING UP...");
  delay(5000);

  lcd.clear();
  lcd.print("COLLECTING ALL");
  lcd.setCursor(0, 1);
  lcd.print("RESOURCE FILES");
  delay(5000);

  lcd.clear();
  lcd.print("ALL CONNECTIONS");
  lcd.setCursor(0, 1);
  lcd.print("ESTABLISHED");
  delay(5000);
  lcd.clear();
  pinMode(buzzer, OUTPUT);

}

void loop()
{
  lcd.clear();
  lcd.print("CAR RUNNING IN");
  lcd.setCursor(0, 1);
  lcd.print("GOOD CONDITION");
  delay(5000);

  lcd.clear();
  lcd.print("DRIVER IS");
  lcd.setCursor(0, 1);
  lcd.print("NOT SLEEPING");
  delay(5000);

  lcd.clear();
  lcd.print("PLS CONCENTRATE");
  lcd.setCursor(0, 1);
  lcd.print("IN DRIVING");
  delay(5000);

  eye = digitalRead(eyepin);
  Serial.println(eye);
  delay(2000);


  if (eye == 0)
  {
    Serial.println(eye);

    lcd.clear();
    lcd.print("DRIVER SLEEPING");
    lcd.setCursor(0, 1);
    lcd.print("PLEASE AWAKE");
    delay(5000);

    digitalWrite(buzzer, HIGH);
    delay(1000);

    lcd.clear();
    lcd.print("TAKE A CUP OF");
    lcd.setCursor(0, 1);
    lcd.print("COFFEE & DRIVE;-)");
    delay(5000);

    digitalWrite(buzzer, LOW);
    delay(10000);

    lcd.clear();

  }
}

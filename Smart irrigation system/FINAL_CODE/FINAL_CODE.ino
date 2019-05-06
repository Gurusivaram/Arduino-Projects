#include "internaltempsensor.h"
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(P2_0, P2_1, P2_2, P2_3, P2_4, P2_5);
SoftwareSerial gsm(6, 7);
int moi = 5;
int mip = 15;
int moidata;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  gsm.begin(9600);
  pinMode(mip, OUTPUT);

  lcd.clear();
  lcd.print("WELCOME TO");
  lcd.setCursor(0, 1);
  lcd.print("GARBAGE MONITOR");
  delay(5000);
}

void loop()
{
  int32_t currentValue = MSPTemp.update();
  digitalWrite(mip, LOW);
  moidata = analogRead(moi); //moisture sensor ah analog ah read panni moidata la store agum
  delay(100);
  Serial.println(moidata);

  if (moidata >= 860)
  {

    farmer();
    delay(1000);

    Serial.println(moidata);
    Serial.println("THERE IS NO ENOUGH WATER IN THE FRILD");
    Serial.println("THE WATER PUMP IS TURNING ON UNTILL THE FIELD BECOMES WET");
    delay(100);

    digitalWrite(mip, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(3000);               // wait for a second
    digitalWrite(mip, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);

    lcd.clear();
    lcd.print("WATER LEVEL IS");
    lcd.setCursor(0, 1);
    lcd.print("LOW IN THE FEILD");
    delay(10000);

    lcd.clear();
    lcd.print("CHECKING THE ");
    lcd.setCursor(0, 1);
    lcd.print("TEMPERATURE");
    delay(10000);

    lcd.clear();
    lcd.print("TEEMPERATURE: ");
    lcd.setCursor(0, 1);
    lcd.print(currentValue / 10, DEC);
    delay(10000);

  }
  else
  {
    lcd.clear();
    lcd.print("ENOUGH WATER ARE");
    lcd.setCursor(0, 1);
    lcd.print("PRESENT IN FEILD");
    delay(10000);

    lcd.clear();
    lcd.print("CHECKING THE ");
    lcd.setCursor(0, 1);
    lcd.print("TEMPERATURE");
    delay(10000);

    lcd.clear();
    lcd.print("TEEMPERATURE: ");
    lcd.setCursor(0, 1);
    lcd.print(currentValue / 10, DEC);
    delay(10000);

    lcd.clear();
    lcd.print("LOOKING GOOD DAY");
    lcd.setCursor(0, 1);
    lcd.print("FOR HARVESTING");
    delay(10000);
  }
}
void farmer()
{
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+919080580113\"\r");
  delay(1000);
  gsm.println("THERE IS NO ENOUGH WATER IN THE FRILD\nTHE WATER PUMP IS TURNING ON UNTILL THE FIELD BECOMES WET");
  delay(1000);
  gsm.println((char)26);
  delay(1000);
}

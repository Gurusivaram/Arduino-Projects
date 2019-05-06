#include <LiquidCrystal.h>
LiquidCrystal lcd(P2_0, P2_1, P2_2, P2_3, P2_4, P2_5);

void setup()
{
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}


void lcd_gps()
{
  lcd.print("GPS data");
}
void lcd_gsm()
{
  lcd.print("GSM data");
}
void lcd_mems()
{
  lcd.print("ACCIDENT data");
}
void lcd_alco()
{
  lcd.print("ALCOHOL data");
}
void lcd_blink()
{
  lcd.print("EYE BLINK data");
}

void loop()
{

}






















//01 - VSS             GND
//02 - VCC             + 5V
//03 - VEE             GND
//04 - RS              Pin8 (P2.0)
//05 - R / W             GND
//06 - EN              Pin9 (P2.1)
//07 - DB0             GND
//08 - DB1             GND
//09 - DB2             GND
//10 - DB3             GND
//11 - DB4             Pin10 (P2.2)
//12 - DB5             Pin11 (P2.3)
//13 - DB6             Pin12 (P2.4)
//14 - DB7             Pin13 (P2.5)
//15 - BL +             +5V
//16 - BL -             GND

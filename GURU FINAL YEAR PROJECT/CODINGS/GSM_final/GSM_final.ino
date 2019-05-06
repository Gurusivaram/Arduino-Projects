#include <SoftwareSerial.h>
SoftwareSerial gsm(6, 7); //syntax is (rx,tx)

void setup()
{
  gsm.begin(9600);
  Serial.begin(9600);
  delay(100);
}

void full()
{
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+919659531937\"\r");
  delay(1000);
  gsm.println("Hello sir/Madam,\n Your Bin is running out of strorage.\n Please check the Bin and make it empty");
  delay(1000);
  gsm.println((char)26);
  delay(1000);
}


void loop()
{
  full();
}

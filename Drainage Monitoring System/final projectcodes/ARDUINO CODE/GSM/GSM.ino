#include <SoftwareSerial.h>
SoftwareSerial gsm(6, 7); //syntax is (rx,tx)

void setup()
{
  gsm.begin(9600);
  Serial.begin(9600);
  delay(100);
}


void loop()
{
  hospital();
  delay(1000);
  police();
  delay(1000);
  family();
  delay(1000);
}

void police()
{
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+919659531937\"\r");
  delay(1000);
  gsm.println("TN47 AK 4747\nMr.Guru\nACCIDENT LOCATION:");

  delay(1000);
  gsm.println((char)26);
  delay(1000);
}
void hospital()
{
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+919659531937\"\r");
  delay(1000);
  gsm.println("MrGGuru\nAGE:30\nANY DISEASES:NIL\nBLOOD:B+\nACCIDENT LOCATION:");

  delay(1000);
  gsm.println((char)26);
  delay(1000);
}
void family()
{
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+919659531937\"\r");
  delay(1000);
  gsm.println("URGENT,\nI HAVE BEEN MET IN AN ACCIDENT.SO PLEASE ARIVE AS SOON AS POSSIBLE TO THE LOCATION AND PLEASE SAVE ME.\nLOCATION:");

  delay(1000);
  gsm.println((char)26);//
  delay(1000);
}


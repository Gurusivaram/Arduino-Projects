#include <SoftwareSerial.h>
SoftwareSerial gsm(6, 7); //syntax is (rx,tx)

void setup()
{
  gsm.begin(9600);
  Serial.begin(9600);
  delay(100);
}

void police()
{
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+919659531937\"\r");
  delay(1000);
  gsm.println("GSM TEST\nTO POLICE:\n1.NUMBER PLATE:TN47 AK 4747\n2.CAR CHASE NO:MER7890TN2018KRRBRD\n3.CAR OWNER:Mr.GOVINDHA PERUMAL\n4.ACCIDENT LOCATION:(GPS)");
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
  gsm.println("GSM TEST\nTO HOSPITAL:\n1.PATIENT NAME:Mr.GOVINDHA PERUMAL\n2.AGE:30\n3.ANY DISEASES:NIL\n4.BLOOD:B+\n5.ACCIDENT LOCATION:(GPS DATA)");
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
  gsm.println("GSM TEST\nTO FAMILY:\n\nURGENT,\nI HAVE BEEN MET IN AN ACCIDENT IN(GPS DATA).SO PLEASE ARIVE AS SOON AS POSSIBLE TO THE LOCATION AND PLEASE SAVE ME.");
  delay(1000);
  gsm.println((char)26);//
  delay(1000);
}

void loop()
{
  hospital();
  police();
  family();
}

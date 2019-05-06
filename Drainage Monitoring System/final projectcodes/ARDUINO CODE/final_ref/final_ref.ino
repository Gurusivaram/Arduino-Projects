
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;

LiquidCrystal lcd(6,7,8,9,10,11);
SoftwareSerial gps(5, 6);
SoftwareSerial gsm(3, 4); //syntax is (rx,tx)


int eye ;


int alc ;


int Gpsdata;             // for incoming serial data
unsigned int finish = 0; // indicate end of message
unsigned int pos_cnt = 0; // position counter
unsigned int lat_cnt = 0; // latitude data counter
unsigned int log_cnt = 0; // longitude data counter
unsigned int flg    = 0; // GPS flag
unsigned int com_cnt = 0; // comma counter
char lat[10];            // latitude array
char lg[10];             // longitude array



void setup()
{
  Serial.begin(9600);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  lcd.begin(16, 2);

  
  pinMode(11, OUTPUT);//buzzer

  gps.begin(9600);

  gsm.begin(9600);

}

void loop()
{

  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);


  lcd.print("Welcome");
  delay(1000);
  lcd.print("Accident Prevention System Starting...");
  delay(1000);

  delay(2000);
  alc = digitalRead(12);
  delay(2000);


  delay(2000);
  eye = digitalRead(10);
  delay(2000);


  delay(2000);
  Vector normAccel = mpu.readNormalizeAccel();
  int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis)) * 180.0) / M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis) * 180.0) / M_PI;
  delay(2000);


  if (alc>= 100)
  {
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);

    Serial.println(alc);
    lcd.print("Driver is drunken");
    delay(2000);
    lcd.print("Car will not start and take rest");
    delay(2000);
  }


  if (eye == 0)
  {
    lcd.print("Driver is feeling sleepy,take rest.");
    Serial.println(eye);
    digitalWrite(11, HIGH);
    delay(2000);
    digitalWrite(11, LOW);
    delay(2000);
  }




  if (pitch == 100 || roll == 100)
  {
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);

    Serial.print(" Pitch = ");
    Serial.print(pitch);
    Serial.print(" Roll = ");
    Serial.print(roll);
    Serial.println();
    delay(10);

    Receive_GPS_Data();
    Serial.print("Latitude  : ");
    Serial.println(lat);
    Serial.print("Longitude : ");
    Serial.println(lg);
    finish = 0;
    pos_cnt = 0;

    hospital();
    police();
    family();

  }




}



void Receive_GPS_Data()
{
  while (finish == 0) {
    while (gps.available() > 0) {     // Check GPS data
      Gpsdata = gps.read();
      flg = 1;
      if ( Gpsdata == '$' && pos_cnt == 0) // finding GPRMC header
        pos_cnt = 1;
      if ( Gpsdata == 'G' && pos_cnt == 1)
        pos_cnt = 2;
      if ( Gpsdata == 'P' && pos_cnt == 2)
        pos_cnt = 3;
      if ( Gpsdata == 'R' && pos_cnt == 3)
        pos_cnt = 4;
      if ( Gpsdata == 'M' && pos_cnt == 4)
        pos_cnt = 5;
      if ( Gpsdata == 'C' && pos_cnt == 5 )
        pos_cnt = 6;
      if (pos_cnt == 6 &&  Gpsdata == ',') { // count commas in message
        com_cnt++;
        flg = 0;
      }

      if (com_cnt == 3 && flg == 1) {
        lat[lat_cnt++] =  Gpsdata;         // latitude
        flg = 0;
      }

      if (com_cnt == 5 && flg == 1) {
        lg[log_cnt++] =  Gpsdata;         // Longitude
        flg = 0;
      }

      if ( Gpsdata == '*' && com_cnt >= 5) {
        com_cnt = 0;                      // end of GPRMC message
        lat_cnt = 0;
        log_cnt = 0;
        flg     = 0;
        finish  = 1;

      }
    }
  }
}



void police()
{
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+919659531937\"\r");
  delay(1000);
  gsm.println("TN47 AK 4747\nMr.Guru\nACCIDENT LOCATION:");
  gsm.print(lat);
  gsm.print(lg);
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
  gsm.print(lat);
  gsm.print(lg);
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
  gsm.print(lat);
  gsm.print(lg);
  delay(1000);
  gsm.println((char)26);//
  delay(1000);
}



//int motorPin1 = 6;
//int motorPin2 = 7;
//int motorPin3 = 8;
//int motorPin4 = 9;
//int eye = 10;
//int eye_buzzer = 11;
//int sensor_pin = 12;

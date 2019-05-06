#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int Xaxis;
int Yaxis;
int Zaxis;

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial gsm(6, 7); //syntax is (rx,tx)
SoftwareSerial gps(2, 4);

int Gpsdata;             // for incoming serial data
unsigned int finish = 0; // indicate end of message
unsigned int pos_cnt = 0; // position counter
unsigned int lat_cnt = 0; // latitude data counter
unsigned int log_cnt = 0; // longitude data counter
unsigned int flg    = 0; // GPS flag
unsigned int com_cnt = 0; // comma counter
char lat[20];            // latitude array
char lg[20];             // longitude array

int motorPin1 = A0;
int motorPin2 = A1;
int motorPin3 = A2;
int motorPin4 = A3;
int alcpin = 5;
int alc = 1;



void setup()
{
  Serial.begin(9600);

  gsm.begin(9600);
  gps.begin(9600);

  Serial.println("INITIATING MPU6050");
  //  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  //{
  //Serial.println("MPU6050 NOT CONNECTED!");
  //delay(500);
  //}
  // mpu.calibrateGyro();
  //mpu.setThreshold(3);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);


  lcd.begin(16, 2);

  lcd.clear();
  lcd.print("     WELCOME");
  delay(5000);

  lcd.clear();
  lcd.print("SYSTEM IS");
  lcd.setCursor(0, 1);
  lcd.print("BOOTING UP...");
  delay(5000);

  lcd.clear();
  lcd.print("SYSTEM RUNNING");
  lcd.setCursor(0, 1);
  lcd.print("DRIVER IS OKAY");
  delay(5000);

  lcd.clear();
  lcd.print("CAR ENGINE IS");
  lcd.setCursor(0, 1);
  lcd.print("STARTING...");
  delay(5000);
}


void loop()
{
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, HIGH);


  //Vector rawGyro = mpu.readRawGyro();
  ///Vector normGyro = mpu.readNormalizeGyro();
  //Xaxis = rawGyro.XAxis;
  //Yaxis = rawGyro.YAxis;
  //Zaxis = rawGyro.ZAxis;

  Serial.print(" Xraw = ");
  Serial.print(Xaxis);
  Serial.print(" Yraw = ");
  Serial.print(Yaxis);
  Serial.print(" Zraw = ");
  Serial.println(Zaxis);


  if (Xaxis > 5000 || Yaxis > 5000 || Zaxis > 5000 || Xaxis < -5000 || Yaxis < -5000 || Zaxis < -5000)
  {

    hospital();
    police();
    family();

    lcd.clear();
    lcd.print("CAR MET IN AN");
    lcd.setCursor(0, 1);
    lcd.print("ACCIDENT");
    delay(5000);

    Receive_GPS_Data();
    Serial.print("LATITUDE  : ");
    Serial.println(lat);
    Serial.print("LONGITUDE : ");
    Serial.println(lg);
    finish = 0; pos_cnt = 0;

    lcd.clear();
    lcd.print("CALL TO THE ");
    lcd.setCursor(0, 1);
    lcd.print("EMERGENCY NO.");
    delay(5000);

    lcd.clear();
    lcd.print("Home");
    lcd.setCursor(0, 1);
    lcd.print("PH:8667030952");
    delay(5000);
  }

  delay(100);
  alc = digitalRead(alcpin);
  Serial.println(alc);
  delay(1000);

  if (alc == 0)
  {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);


    Serial.println(alc);
    lcd.clear();
    lcd.print("DRIVER IS DRUNKEN");
    lcd.setCursor(0, 1);
    lcd.print("CAR NOT START");
    delay(15000);
  }



  lcd.clear();
  lcd.print("CAR NOT GET");
  lcd.setCursor(0, 1);
  lcd.print("ACCIDENT");
  delay(5000);

  lcd.clear();
  lcd.print("LATITUDE AND ");
  lcd.setCursor(0, 1);
  lcd.print("LONGITUDE ARE");
  delay(5000);

  //lcd.clear();
  //lcd.print(lat);
  //lcd.setCursor(0, 1);
  //lcd.print(lg);
  //delay(5000);

  lcd.clear();
  lcd.print("VEHICLE AXIS");
  lcd.setCursor(0, 1);
  lcd.print("ARE NORMAL");
  delay(5000);

  lcd.clear();
  lcd.print("Xaxis");
  lcd.setCursor(0, 1);
  lcd.print(Xaxis);
  delay(5000);

  lcd.clear();
  lcd.print("Yaxis");
  lcd.setCursor(0, 1);
  lcd.print(Yaxis);
  delay(5000);

  lcd.clear();
  lcd.print("Zaxis");
  lcd.setCursor(0, 1);
  lcd.print(Zaxis);
  delay(5000);

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
  gsm.println("MrGGuru\nAGE:30\nANY DISEASES:NIL\nBLOOD:B+\nACCIDENT LOCATION:%f");
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

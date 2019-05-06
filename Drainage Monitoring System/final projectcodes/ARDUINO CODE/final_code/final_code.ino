#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int Xaxis;
int Yaxis;
int Zaxis;

const int rs = 12, en = 13, d4 = 9, d5 = 10, d6 = 11, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial gsm(4, 5); //syntax is (rx,tx)
SoftwareSerial gps(7, 8);

int Gpsdata;             // for incoming serial data
unsigned int finish = 0; // indicate end of message
unsigned int pos_cnt = 0; // position counter
unsigned int lat_cnt = 0; // latitude data counter
unsigned int log_cnt = 0; // longitude data counter
unsigned int flg    = 0; // GPS flag
unsigned int com_cnt = 0; // comma counter
char lat[20];            // latitude array
char lg[20];             // longitude array




void setup()
{
  Serial.begin(9600);
  gsm.begin(9600);
  gps.begin(9600);

  Serial.println("Inicjalizacja MPU6050");
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Nie mozna znalezc MPU6050 - sprawdz polaczenie!");
    delay(500);
  }
  mpu.calibrateGyro();
  mpu.setThreshold(3);

  lcd.begin(16, 2);

  lcd.clear();
  lcd.print("     WELCOME");
  delay(5000);

  lcd.clear();
  lcd.print("System is");
  lcd.setCursor(0, 1);
  lcd.print("Booting up...");
  delay(5000);

  lcd.clear();
  lcd.print("Car Engine is");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(5000);

  lcd.clear();
  lcd.print("System Running");
  lcd.setCursor(0, 1);
  lcd.print("Driver OK");
  delay(5000);


}
void loop()
{
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();
  Xaxis = rawGyro.XAxis;
  Yaxis = rawGyro.YAxis;
  Zaxis = rawGyro.ZAxis;

  Serial.print(" Xraw = ");
  Serial.print(Xaxis);
  Serial.print(" Yraw = ");
  Serial.print(Yaxis);
  Serial.print(" Zraw = ");
  Serial.println(Zaxis);


  lcd.clear();
  lcd.print("Car not get");
  lcd.setCursor(0, 1);
  lcd.print("accident");
  delay(5000);

  lcd.clear();
  lcd.print("Latitude and ");
  lcd.setCursor(0, 1);
  lcd.print("Longitude are");
  delay(5000);

  lcd.clear();
  lcd.print("Vehicle axis");
  lcd.setCursor(0, 1);
  lcd.print("are normal");
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



  if (Xaxis > 5000 || Yaxis > 5000 || Zaxis > 5000 || Xaxis < -5000 || Yaxis < -5000 || Zaxis < -5000)
  {

    hospital();
    police();
    family();

    lcd.clear();
    lcd.print("Car met in an");
    lcd.setCursor(0, 1);
    lcd.print("accident");
    delay(5000);

    Receive_GPS_Data();
    Serial.print("Latitude  : ");
    Serial.println(lat);
    Serial.print("Longitude : ");
    Serial.println(lg);
    finish = 0; pos_cnt = 0;

    lcd.clear();
    lcd.print("Call to the ");
    lcd.setCursor(0, 1);
    lcd.print("emergency NO.");
    delay(5000);

    lcd.clear();
    lcd.print("Home");
    lcd.setCursor(0, 1);
    lcd.print("PH:8667030952");
    delay(5000);
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

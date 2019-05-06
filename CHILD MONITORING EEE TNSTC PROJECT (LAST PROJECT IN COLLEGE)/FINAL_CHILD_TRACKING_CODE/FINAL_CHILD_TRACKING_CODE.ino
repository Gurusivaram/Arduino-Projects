#include<TinyGPS++.h>
#include<SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>
#include "ThingSpeak.h"
#define BLYNK_MAX_SENDBYTES 256

double latitude, longitude;
static const int RX = 14, TX = 12;
String bearing, latbuf, lonbuf, lati, lon, homelat = "10.96", homelon = "78.07", stationlat = "10.95", stationlon = "78.07", nsnlat = "10.89", nsnlon = "78.02";

TinyGPSPlus gps;
BlynkTimer timer;
WiFiClient  client;
SoftwareSerial test_GPS(RX, TX);
WidgetMap myMap(V5);
WidgetLCD lcd(V6);

char auth[] = "bc2fc5b504e84f6981ac5e91ab38a7f3";
char ssid[] = "Ap";
char pass[] = "11111111";
unsigned long myChannelNumber = 750168;
const char * myWriteAPIKey = "NZ37R1LFQD07TP07";

void setup()
{
  Serial.begin(115200);
  Serial.println();
  test_GPS.begin(9600);
  Blynk.begin(auth, ssid, pass);
  ThingSpeak.begin(client);

  lcd.clear();
  myMap.clear();
  Blynk.virtualWrite(V1, "------ -");
  Blynk.virtualWrite(V2, "------ -");
  Blynk.virtualWrite(V3, "------ -");
  Blynk.notify("The device is connected");
}

void loop()
{
  while (test_GPS.available() > 0)
  {
    if (gps.encode(test_GPS.read()))
    {
      displayInfo();
    }
  }
  Blynk.run();
  timer.run();
  checkGPS();
}

void displayInfo()
{
  delay(5000);
  if (gps.location.isValid())
  {
    latitude =gps.location.lat();
    Serial.print("LAT:  ");
    Serial.println(latitude);
    Blynk.virtualWrite(V1, latitude);

    longitude = gps.location.lng();
    Serial.print("LONG: ");
    Serial.println(longitude);
    Blynk.virtualWrite(V2, longitude);

    String lati = (String(latitude, 2));
    String lon = (String(longitude, 2));

    if (lati == homelat && lon == homelon)
    {
      Serial.println("your child is in home");
      lcd.clear();
      lcd.print(0, 0, "Your child is");
      lcd.print(0, 1, "near by home");
    }

    else if (lati == stationlat && lon == stationlon)
    {
      Serial.println("your child is in bus stop");
      lcd.clear();
      lcd.print(0, 0, "Your child is");
      lcd.print(0, 1, "in bus stop");
    }

    else if (lati == nsnlat && lon == nsnlon)
    {
      Serial.println("your child is in school");
      lcd.clear();
      lcd.print(0, 0, "Your child is");
      lcd.print(0, 1, "in school");
    }

    else
    {
      Serial.println("your child is not present in any defined location");
      lcd.clear();
      lcd.print(0, 0, "Your child is");
      lcd.print(0, 1, "not in defined area");
      Blynk.notify("Your child is not in any known location. So please chack the status immeditely and report to police if the child is lost");
    }

    bearing = TinyGPSPlus::cardinal(gps.course.value());
    Blynk.virtualWrite(V3, bearing);

    myMap.clear();
    myMap.location(0, latitude, longitude, "Child");

    latbuf += (String(latitude, 6));
    lonbuf += (String(longitude, 6));

    ThingSpeak.setField(1, latbuf);
    ThingSpeak.setField(2, lonbuf);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  }
}

void checkGPS()
{
  if (gps.charsProcessed() < 10)
  {
    Blynk.notify("The device in child's shoe is disconnected or damaged. Please wait until it reconnects");
    Serial.println("No GPS detected: check wiring.");

    myMap.clear();
    lcd.clear();
    lcd.print(0, 0, "Device is");
    lcd.print(0, 1, "disconnected");

    Blynk.virtualWrite(V1, "-------");
    Blynk.virtualWrite(V2, "-------");
    Blynk.virtualWrite(V3, "-------");
  }
}

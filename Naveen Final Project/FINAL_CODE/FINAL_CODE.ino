#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define WIFI_SSID "Mani"
#define WIFI_PASS "11111111"
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "manijairam0607"
#define MQTT_PASS "c401a5c36ed24a8f91e9df8a3366c435"
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
Adafruit_MQTT_Subscribe onoff = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/onoff");
void setup()
{
  Serial.begin(9600);
  Serial.print("\n\nConnecting Wifi... ");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Serial.println("OK!");
  mqtt.subscribe(&onoff);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
}
void loop()
{
  MQTT_connect();
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    if (subscription == &onoff)
    {
      Serial.println((char*) onoff.lastread);

      if (!strcmp((char*) onoff.lastread, "lightoneon"))
      {
        digitalWrite(D1, LOW);
      }
      else if (!strcmp((char*) onoff.lastread, "lightoneoff"))
      {
        digitalWrite(D1, HIGH);
      }
      else if (!strcmp((char*) onoff.lastread, "lighttwoon"))
      {
        digitalWrite(D2, LOW);
      }
      else if (!strcmp((char*) onoff.lastread, "lighttwooff"))
      {
        digitalWrite(D2, HIGH);
      }
      else if (!strcmp((char*) onoff.lastread, "fanon"))
      {
        digitalWrite(D3, LOW);
      }
      else if (!strcmp((char*) onoff.lastread, "fanoff"))
      {
        digitalWrite(D3, HIGH);
      }
      else if (!strcmp((char*) onoff.lastread, "plugon"))
      {
        digitalWrite(D4, LOW);
      }
      {
        digitalWrite(D4, HIGH);
      }

    }
  }
  if (!mqtt.ping())
  {
    mqtt.disconnect();
  }
}
void MQTT_connect()
{
  int8_t ret;
  if (mqtt.connected())
  {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0)
  {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0)
    {
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}



#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3);
String command;
void setup()
{
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite (6, HIGH);
  digitalWrite (7, HIGH);
}

void loop()
{
  while (BT.available())
  {
    delay(10);
    char c = BT.read();
    command += c;
  }
  if (command.length() > 0)
  {
    Serial.println(command);

    if (command == "on1")
    {
      digitalWrite(6, LOW);
      Serial.println("light on");
    }
    else if (command == "off1")
    {
      Serial.println("light off");
      digitalWrite (6, HIGH);
    }
    else if (command == "on2")
    {
      digitalWrite (7, LOW);
      Serial.println("lamp on");
    }
    else if ( command == "off2")

    {
      digitalWrite (7, HIGH);
      Serial.println("lamp off");
    }
    else if (command == "af")
    {
      digitalWrite (6, HIGH);
      digitalWrite (7, HIGH);
      Serial.println("OFF");
    }
    command = "";
  }
}

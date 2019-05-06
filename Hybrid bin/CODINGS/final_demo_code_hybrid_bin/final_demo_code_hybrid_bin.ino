#include <SoftwareSerial.h>
SoftwareSerial gsm(P1_5, P2_0);
#include <Stepper.h> //header file for stepper motor controlling
const int steps = 70; //sets the number of steps required to complete one revoluation i.e. 360 degree rotation
int enA = P2_7 ; //it sets high upto 255 for motor 1 enable in L298N
int enB = P2_6; //it sets high upto 255 for motor 2 enable in L298N
int mip1 = P2_2; //to control motor pin1(A+) BLACK COLOUR in OUT1 at L298N bridge
int mip2 = P2_5; //to control motor pin2(A-) GREEN COLOUR in OUT2 at L298N bridge
int mip3 = P1_6; //to control motor pin3(B+) BLUE COLOUR in OUT3 at L298N bridge
int mip4 = P1_7; //to control motor pin4(B-) RED COLOUR in OUT4 at L298N bridge
Stepper motor(steps, mip1, mip2, mip3, mip4); //function definition with s/p and four input ports

const int tp1 = P2_3; //digital pin 3 for triggering the ultrasonic sensor
const int ep1 = P2_4; //digital pin 4 for getting the echo from the ultrasonic sensor
long duration1; //to store the duration of the sound wave travels in ultrasonic sensor

const int tp2 = P1_0 ; //digital pin 3 for triggering the ultrasonic sensor( to find bin is full or not)
const int ep2 = P1_1 ; //digital pin 4 for getting the echo from the ultrasonic sensor( to find bin is full or not)
long duration2; //to store the duration of the sound wave travels in ultrasonic sensor( to find bin is full or not)

int moi = P1_4; //analog pin A0 for moisture sensor
int moidata; //to store moisture sensor data

int in = P2_1; //digital pin 2 for inductive sensor
int indata; // to store inductive sensor data


void  setup()

{
  Serial.begin(9600); //initialize the serial monitor
  gsm.begin(9600);

  motor.setSpeed(50);
  analogWrite(enA, 200);
  analogWrite(enB, 200);

  pinMode(tp1, OUTPUT); //setting digital pin 3 as output for the ultrasonic sensor to trigger
  pinMode(ep1, INPUT); //setting digital pin 4 to get the echo output from ultrasonic sensor
  pinMode(tp2, OUTPUT); //setting digital pin 3 as output for the ultrasonic sensor to trigger
  pinMode(ep2, INPUT); //setting digital pin 4 to get the echo output from ultrasonic sensor
}


void loop()

{
  digitalWrite(tp1, LOW);
  delayMicroseconds(2);

  digitalWrite(tp1, HIGH);
  delayMicroseconds(10);

  digitalWrite(tp1, LOW);
  duration1 = pulseIn(ep1, HIGH);
  delay(100);


  Serial.println(duration1);

  if (duration1 > 300 && duration1 < 3000)

  {
    delay(2000);
    moidata = analogRead(moi); //moisture sensor ah analog ah read panni moidata la store agum
    delay(2000);
    indata = digitalRead(in); //inductive seor ah digital ah read panni indata la store agum
    delay(2000); //adhukapram one second delay in overall program

    if (indata == 1) //inga dha loop start avudhu and inductive data equal to one naa matum dha indha loop execute agum

    {
      Serial.println(indata); //inga serial monitor la data print agum
      Serial.println("it is an metal"); //idhu metal aah nu dha first check panu.. metal ilana matum dha nexxt step move agum
      delay(100); //process mudinja aprm one second delay in the program

      motor.step(-steps);
      delay(500);
      motor.step(0);
      delay(500);

      motor.step(steps);
      delay(500);
      motor.step(0);
      delay(500);

      digitalWrite(mip1, LOW);
      digitalWrite(mip2, LOW);
      digitalWrite(mip3, LOW);
      digitalWrite(mip4, LOW);
    }

    else if (moidata == 0) //inga moisture sensor  output is ture naa adhu kandipa food waste ah dha rukum nu nama assume panikanum

    {
      Serial.println(moidata);
      Serial.println("it is an metal");
      delay(100);

      motor.step(-steps);
      delay(500);
      motor.step(0);
      delay(500);

      motor.step(steps);
      delay(500);
      motor.step(0);
      delay(500);

      digitalWrite(mip1, LOW);
      digitalWrite(mip2, LOW);
      digitalWrite(mip3, LOW);
      digitalWrite(mip4, LOW);
    }


    else if (moidata < 1005) //inga moisture sensor  output is ture naa adhu kandipa food waste ah dha rukum nu nama assume panikanum

    {
      Serial.println(moidata);
      Serial.println("it is an organic material");
      delay(100);

      motor.step(steps);
      delay(500);
      motor.step(0);
      delay(500);

      motor.step(-steps);
      delay(320);
      motor.step(0);
      delay(500);

      digitalWrite(mip1, LOW);
      digitalWrite(mip2, LOW);
      digitalWrite(mip3, LOW);
      digitalWrite(mip4, LOW);
    }



    else if (moidata > 1010 && indata == 0) //this loop means that the waste is neither food nor metal then we assume that the waste is plastic
    {

      Serial.println("it is an plastic"); //inga nama plastic nu assume pani loop ah again run panuvom for repetition
      delay(100); //process mudinja aprm one second delay in the program

      motor.step(-steps);
      delay(200);
      motor.step(0);
      delay(1000);

      motor.step(steps);
      delay(300);
      motor.step(0);
      delay(1000);

      digitalWrite(mip1, LOW);
      digitalWrite(mip2, LOW);
      digitalWrite(mip3, LOW);
      digitalWrite(mip4, LOW);
    }

  }

  if (duration2 < 2000 & duration2 > 1000)
  {
    delay(100);
    owner();
    delay(100);
    Serial.println("bin is full");
  }
}

void owner()
{
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+919659531937\"\r");
  delay(1000);
  gsm.println("BIN IS FULL PLEASE COME AND CLEAN THE BIN NO.2 IN ANNANAGAR");
  delay(1000);
  gsm.println((char)26);
  delay(1000);
}

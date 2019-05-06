#include <Stepper.h> //header file for stepper motor controlling
const int steps = 25; //sets the number of steps required to complete one revoluation i.e. 360 degree rotation
int enA = 5; //it sets high upto 255 for motor 1 enable in L298N
int enB = 6; //it sets high upto 255 for motor 2 enable in L298N
int mip1 = 7; //to control motor pin1(A+) BLACK COLOUR in OUT1 at L298N bridge
int mip2 = 8; //to control motor pin2(A-) GREEN COLOUR in OUT2 at L298N bridge
int mip3 = 9; //to control motor pin3(B+) BLUE COLOUR in OUT3 at L298N bridge
int mip4 = 10; //to control motor pin4(B-) RED COLOUR in OUT4 at L298N bridge
Stepper motor(steps, mip1, mip2, mip3, mip4); //function definition with s/p and four input ports

const int tp = 3; //digital pin 3 for triggering the ultrasonic sensor
const int ep = 4; //digital pin 4 for getting the echo from the ultrasonic sensor
long duration; //to store the duration of the sound wave travels in ultrasonic sensor

int moi = A0; //analog pin A0 for moisture sensor
int moidata; //to store moisture sensor data

int in = A1; //digital pin 2 for inductive sensor
int indata; // to store inductive sensor data


void  setup()

{
  motor.setSpeed(100);
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  pinMode(tp, OUTPUT); //setting digital pin 3 as output for the ultrasonic sensor to trigger
  pinMode(ep, INPUT); //setting digital pin 4 to get the echo output from ultrasonic sensor
  Serial.begin(9600); //initialize the serial monitor

}


void loop()

{
  digitalWrite(tp, LOW);
  delayMicroseconds(2);

  digitalWrite(tp, HIGH);
  delayMicroseconds(10);

  digitalWrite(tp, LOW);
  duration = pulseIn(ep, HIGH);
  delay(100);


  Serial.println(duration);

  if (duration < 3500 || duration > 10000)

  {
    delay(1000);
    moidata = analogRead(moi); //moisture sensor ah analog ah read panni moidata la store agum
    delay(1000);
    indata = analogRead(in); //inductive seor ah digital ah read panni indata la store agum
    delay(1000); //adhukapram one second delay in overall program

    if (indata > 100) //inga dha loop start avudhu and inductive data equal to one naa matum dha indha loop execute agum

    {
      Serial.println(indata); //inga serial monitor la data print agum
      Serial.println("it is an metal"); //idhu metal aah nu dha first check panu.. metal ilana matum dha nexxt step move agum
      delay(100); //process mudinja aprm one second delay in the program

      motor.step(-steps);
      delay(500);
      motor.step(0);
      delay(2000);

      motor.step(steps);
      delay(100);
      motor.step(0);
      delay(100);

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
      delay(2000);

      motor.step(steps);
      delay(500);
      motor.step(0);
      delay(100);

      digitalWrite(mip1, LOW);
      digitalWrite(mip2, LOW);
      digitalWrite(mip3, LOW);
      digitalWrite(mip4, LOW);
    }


    else if (moidata < 1005 & moidata > 40) //inga moisture sensor  output is ture naa adhu kandipa food waste ah dha rukum nu nama assume panikanum

    {
      Serial.println(moidata);
      Serial.println("it is an organic material");
      delay(100);

      motor.step(steps);
      delay(500);
      motor.step(0);
      delay(2000);

      motor.step(-steps);
      delay(500);
      motor.step(0);
      delay(100);

      digitalWrite(mip1, LOW);
      digitalWrite(mip2, LOW);
      digitalWrite(mip3, LOW);
      digitalWrite(mip4, LOW);
    }



    else if (moidata > 1000 & indata < 10) //this loop means that the waste is neither food nor metal then we assume that the waste is plastic
    {

      Serial.println("it is an plastic"); //inga nama plastic nu assume pani loop ah again run panuvom for repetition
      delay(100); //process mudinja aprm one second delay in the program

      motor.step(-steps);
      delay(500);
      motor.step(0);
      delay(2000);

      motor.step(steps);
      delay(50);
      motor.step(0);
      delay(1000);

      digitalWrite(mip1, LOW);
      digitalWrite(mip2, LOW);
      digitalWrite(mip3, LOW);
      digitalWrite(mip4, LOW);
    }

  }
}


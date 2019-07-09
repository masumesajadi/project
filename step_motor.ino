/*
 * Driving a 5V stepper motor using Keyes L298N Dual Motor Driver;
 * Chienline @2015;
 */

const int ENA = 2;
const int IN1 = 3;
const int IN2 = 4;
const int ENB = 7;
const int IN4 = 5;
const int IN3 = 6;
//const int ledPin = 13;

void setup()
{
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  //pinMode(ledPin,OUTPUT);
  //digitalWrite(ledPin, LOW);

  //delay is used to control the speed, the lower the faster.
  //reverse(step,delay);
  reverse(180,20);
  reverse(180,5);
  reverse(180,20);
  
  
  //forward(step,delay);
  forward(80,5);
}

void loop()
{
}

void reverse(int i, int j) {

  // set both motors ON
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);

  while (1)   {
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
    delay(j);
    i--;
    if (i < 1) break; 

    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
    delay(j);  
    i--;
    if (i < 1) break;

    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
    delay(j);
    i--;
    if (i < 1) break;

    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
    delay(j);  
    i--;
    if (i < 1) break;
  }

  // set both motors OFF
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  
}  // end reverse()

void forward(int i, int j) {

  // Set both motors ON
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);

  while (1)   {
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
    delay(j);  
    i--;
    if (i < 1) break;

    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
    delay(j);
    i--;
    if (i < 1) break;

    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
    delay(j);  
    i--;
    if (i < 1) break;

    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
    delay(j);
    i--;
    if (i < 1) break;
  }

  // set both motors OFF
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);

}  // end forward()

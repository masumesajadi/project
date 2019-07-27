#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <ArduinoHardware.h>
#include <Wire.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 8 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);


const int ENA = 2;
const int IN1 = 3;
const int IN2 = 4;
const int ENB = 7;
const int IN4 = 5;
const int IN3 = 6;

int i;
int value;
int temperature;
int s=0;
float angle_new; 
int desire;
int b=1;
int x=0;
float sth;
float temp;
byte a ,c; 
String var;
int desire;

void setup(){
  pinMode(13, OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  
  sensors.begin(); 

  Serial.begin(9600);              //Starting serial communication
}

void loop(){

  //// Read Desire from Rpi
  while (!Serial.available()){}
  
  while (Serial.available()){
    c = Serial.read();
    
    a = c-48 ;
    var += String (a);
    delay(1000);
  }
   
   desire=var.toInt();
   //Serial.println(desire);
   var="";
    
  delay(10);
  Temperature(desire);
  delay(100);
  Serial.println("The Project has Done!!!");
  Serial.println("The angle of motor is: ");
  Serial.print(sth);
  Serial.println("The amount of temp is: ");
  Serial.print(temp);  
}



///////////////// Temperature Function \\\\\\\\\\\\\\\\\\\
void Temperature(int desire){  
  
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  temp = sensors.getTempCByIndex(0);
  
  delay(1000);
  
  /////*********************** FORWARD **********************************
  
   while((s < 4) && (temp < desire)){  // we shoud increase light by opening the curtain
      x++;
      forward(506.25,5);
      delay(1000);
      
      sensors.requestTemperatures(); // Send the command to get temperature readings 
      temp = sensors.getTempCByIndex(0);
  
      if((temp > desire)){
       s++;
       sth=angle(s,b);
      }
      else{s++;}
      sth=angle(s,b);
   }
      
      sensors.requestTemperatures(); // Send the command to get temperature readings 
      temp = sensors.getTempCByIndex(0);
  
      if((temp < desire)){
        delay(10);
        digitalWrite(13, HIGH-digitalRead(13)); //////Heater on
      }
   
   
   
    
  /////*********************** REVERSE **********************************
  if(x == 0){    
    while((s < 4) && (temp > desire)){  // we shoud decrease temp by closing the shoofazh
         
       sensors.requestTemperatures(); // Send the command to get temperature readings 
       temp = sensors.getTempCByIndex(0);
       
       if((temp > desire)){
          reverse(506.25,5);
          delay(1000);
          s++;
       }
       
       else{
           sth=angle(s,b); 
       }
      
       sth=angle(s,b);
    }
  }
}


/////======================= Angle Function
float angle(int s , int b){ 
    angle_new = ((s*506.25)/5.625)*b;
  return  angle_new;  
  }
////=======================================

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

}


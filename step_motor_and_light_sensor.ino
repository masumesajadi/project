
#include <Wire.h>
  int BH1750_address = 0x23; // i2c Addresse
  byte buff[2];
const int ENA = 2;
const int IN1 = 3;
const int IN2 = 4;
const int ENB = 7;
const int IN4 = 5;
const int IN3 = 6;
  int light;
  int place=2;
  int endpoint=100;
  int startpoint=0;
  int i;
  int value;

  void setup(){

  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
    delay(200);
    Serial.begin(9600);
  }

  void loop(){
    float valf=0;
    //place=1;
    if(BH1750_Read(BH1750_address)==2){
      valf=((buff[0]<<8)|buff[1])/1.2;
      if(valf<0)Serial.print("> 65535");
      else Serial.print((int)valf,DEC);
      Serial.println(" lx");
      light=valf;
      
      if(light>300)
      { // day
         if(place > 1 ){  //closed
                  /////clockwise
                 forward(80,5);
                  delay (1000);//هر نیم ساعت بیاد ببینه نور در چه حدیه و جهت باید کدوم وری باشه
                  //و قبلش چک کنه ببینه موقعیت موتور و به تبع اون پرئه کجا قرار داره اگه قابلیت چرخش داره خب بچرخه اگه نه هیچ کاری نکنه و نیم ساعت دیگه صبر کنه.
                  place--;
         }
      }
   
 
       if(light<300)
       {  ///night
           if(place <= 1 ){ //opened
                  reverse(180,20);
                  reverse(180,5);
                  reverse(180,20);
                  delay (1000);
                  place++;
       }
       }

    }
    
  }


//==================================================================
  byte BH1750_Read(int address)
  {
    byte i=0;
    Wire.beginTransmission(address);
    Wire.requestFrom(address, 2);
    while(Wire.available()){
      buff[i] = Wire.read();
      i++;
    }
    Wire.endTransmission();  
    return i;
  }

/////========================================





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

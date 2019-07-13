#include <ArduinoHardware.h>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/Float32.h>


#include <geometry_msgs/Twist.h>

#include <Wire.h>

#include <OneWire.h> 
#include <DallasTemperature.h>


int BH1750_address = 0x23; // i2c Addresse
byte buff[2];

/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 

  //create the ros node nh. The node will be used to publish to Arduino
  ros::NodeHandle nh;
  
  //for example, if you're using a Temperature sensor, the sensor message is Temperature
  std_msgs::Float32 temp_msg;
  ros::Publisher pub_temp("temperature", &temp_msg);

  const int ENA = 2;
  const int IN1 = 3;
  const int IN2 = 4;
  const int ENB = 7;
  const int IN4 = 5;
  const int IN3 = 6;
  
  int setpoint_t;
  int setpoint_l;
  int light;
  int temperature;
  int i;
  int value;
  float temp;
  int s=0;
  int b=1;
  float angle_new; 
  float old;
  
  // Stepper Motor function
  //double speed_ang=0, speed_lin=0;
  
  //void messageCb(const geometry_msgs::Twist& msg){
  //  speed_ang = msg.angular.z;
  //  speed_lin = msg.linear.x;
  //}
  
  //ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb);

  void setup(){
   
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
    delay(200);
    
    nh.initNode();
    
    nh.advertise(pub_temp);
 
    //nh.subscribe(sub);
    
    Wire.begin();
    BH1750_Init(BH1750_address);
    
    Serial.begin(115200);
    
    Serial.print("Your Desire is: ");
    // Get a setpoint from user through ros
    if (Serial.available() > 0){
      Serial.read();
      setpoint_t = Serial.parseInt();    /// select one setpoint !!!
      setpoint_l = Serial.parseInt();
    }
    
    //temperature sensor begin    
    Serial.println("Dallas Temperature IC Control Library Demo"); 
    // Start up the library 
    sensors.begin(); 
  }
  
  
void loop(){
  TEMPERATURE();
  ILLUMINANCE();

  nh.spinOnce();    
}

//==================================================================
  
///////***************************************************** Illuminance Function

void ILLUMINANCE(void){
  float valf=0;
  //place=1;
  if(BH1750_Read(BH1750_address)==2){
    valf=((buff[0]<<8)|buff[1])/1.2;
    if(valf<0)Serial.print("> 65535");
    else Serial.print((int)valf,DEC);
    Serial.println(" lx");
    light=valf;
    
      /////// While Forward
  while(light < setpoint_l && s < 16){
   forward(506.25,5);
   
    if(BH1750_Read(BH1750_address)==2){
    valf=((buff[0]<<8)|buff[1])/1.2;
    if(valf<0)Serial.print("> 65535");
    else Serial.print((int)valf,DEC);
    Serial.println(" lx");
    light=valf;
    }
   
   s++;
   Serial.print("The amount of angle is: ");
   angle(s, -b);
  } 
  if(s==15){
    s=0;
  }  
    
  /////// While Reverse
  while(light > setpoint_l && s < 16){
   reverse(506.25,5);
   
    if(BH1750_Read(BH1750_address)==2){
    valf=((buff[0]<<8)|buff[1])/1.2;
    if(valf<0)Serial.print("> 65535");
    else Serial.print((int)valf,DEC);
    Serial.println(" lx");
    light=valf;
    }
   
   s++;
   Serial.print("The amount of angle is: ");
   angle(s, b);
  } 
  if(s==15){
    s=0;
  } 
  } 
}


//////**************** Light_sensor Read

  void BH1750_Init(int address){
    Wire.beginTransmission(address);
    Wire.write(0x10); // 1 [lux] aufloesung
    Wire.endTransmission();
  }
  byte BH1750_Read(int address){
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

//////************************************************ Temperature Function

void TEMPERATURE(void){
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus 
  /********************************************************************/
  Serial.print(" Requesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  Serial.println("DONE"); 
  /********************************************************************/
  temp = sensors.getTempCByIndex(0);
  Serial.print("Temperature is: "); 
  Serial.print(temp); // Why "byIndex"?  
  // You can have more than one DS18B20 on the same bus.  
  // 0 refers to the first IC on the wire 
  Serial.print((char)176);//shows degrees character
  Serial.print("C ");  
  
  delay(2000);
  
  //publish every 60000 milliseconds_60 seconds_1 minute
  //**************************************
  temp_msg.data = temperature;       //  *
  //**************************************
  pub_temp.publish(&temp_msg);
  
  /////// While Forward
  while(temp < setpoint_t && s < 16){
   forward(506.25,5);
   temp = sensors.getTempCByIndex(0);
   s++;
   Serial.print("The amount of angle is: ");
   angle(s, -b);
   delay(1000);
  } 
  if(s==15){
    s=0;
  }  
    
  /////// While Reverse
  while(temp > setpoint_t && s < 16){
   reverse(506.25,5);
   temp = sensors.getTempCByIndex(0);
   s++;
   Serial.print("The amount of angle is: ");
   angle(s, b);
   delay(1000);
  } 
  if(s==15){
    s=0;
  }
}






 /////********************************** Angle Function

void angle(int a, int b){ 
    Serial.print(angle_new = ((a*506.25)/5.625)*b);
    Serial.println((char)176);
    old =+ angle_new;    
  }
  

//////********************************** Motor Movements Functions

void reverse(float i, int j) {

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


void forward(float i, int j) {

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

} // end forward()



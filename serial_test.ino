byte a ,b; 
String var;
int desire;

void setup() {
Serial.begin(9600);              //Starting serial communication
}
  
void loop() {
  while (!Serial.available()){}
  
  while (Serial.available()){
    b = Serial.read();
    
    a= b-48 ;
    var += String (a);
    delay(1000);
  }
   
   desire=var.toInt();
   Serial.println(desire);
   var="";
}

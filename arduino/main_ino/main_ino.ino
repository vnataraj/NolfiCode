#include <Servo.h>

Servo servo;
int pos=0;

void setup(){
	Serial.begin(9600);
	servo.attach(13);
	Serial.println("Okay, serial is instantiated");
}

void loop(){
  //servo.write(90);
  for(pos=0; pos<=180; pos+=180){
   servo.write(pos);
   delay(100);
   Serial.println("forwards loop");
  }
  //delay(100);
  for(pos=180; pos>=0; pos-=180){
   servo.write(pos);
   delay(100);
   Serial.println("backwards loop"); 
  }
  
}

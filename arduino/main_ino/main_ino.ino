#include <Servo.h>

Servo servo;
int pos=0;

void setup(){
	Serial.begin(9600);
	servo.attach(13);
	Serial.println("Okay, serial is instantiated");
}

void loop(){
  for(pos=0; pos<180; pos+=10){
   servo.write(pos);
   delay(300);
   Serial.println("forwards loop");
  }
  delay(300);
  for(pos=180; pos>0; pos-=10){
   servo.write(pos);
   delay(300);
   Serial.println("backwards loop"); 
  }
}

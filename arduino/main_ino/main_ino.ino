#include <Servo.h>

Servo caudal;
int pos=0;
int IR_pin=1;
int caudal_pin=13;

void setup(){
	Serial.begin(9600);
	caudal.attach(caudal_pin);
	Serial.println("Okay, serial is instantiated");
}

void loop(){
  //servo.write(90);
  /*for(pos=0; pos<=180; pos+=180){
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
 */
	writeToCaudalServo(caudal);
  
}

void writeToCaudalServo(Servo servo){
	for(pos=0; pos<=180; pos+=180){
		servo.write(pos);
		delay(100);
	}
	for(pos=180; pos>=0; pos-=180){
		servo.write(pos);
		delay(100);
	}
}

void readIRSensor(int pin){
	float volts = analogRead(pin)*0.0048828125;
	float distance = 65*pow(volts, -1.10);
	Serial.println(distance);
	delay(100);
}

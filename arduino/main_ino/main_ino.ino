#include <Servo.h>
#include <PinChangeInt.h>
#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Wire.h>
#include "main.h"


/* 
 *  DEFINE VARIABLES
 */

Servo caudal;
Servo pectoral1;
Servo pectoral2;
Servo dorsal;
bool left = false;
bool right = false;
bool distance1 = false;
bool distance2 = false;
bool up = false;
bool down = false;

/* SETUP ROUTINE */

void setup(){
	sei();  // enable interrupts
	Serial.begin(9600);
	pinMode(IR_PIN1, INPUT);
	pinMode(IR_PIN2, INPUT);
	//PCIntPort::attachInterrupt(IR_PIN1, actOnDistance1, CHANGE);
	//PCIntPort::attachInterrupt(IR_PIN2, actOnDistance2, CHANGE);
	caudal.attach(CAUDAL_PIN);
	Serial.println("Okay, serial is instantiated");
}

/* FUNCTIONS CALLED BY INTERRUPTS */

void actOnDistance1(){
	distance1=true;
}
void actOnDistance2(){
	distance2=true;
}

void actOnLeft(){
	left=true;
}

void actOnRight(){
	right=true;
}

/* MAIN EXECUTION LOOP */

void loop(){
	startServoRoutine();
}

/* MOTOR FUNCTION */

void startServoRoutine(){
	if(distance1 && distance2){
		//turn right();
		distance1=false;
		distance2=false;
	}
	if(left){
		//tilt right();
		left=false;
	}
	else if(right){
		//tilt left();
		right=false;
	}
	if(up){
		//tilt down();
	}
	else if(down){
		//tilt up();
	}
	writeToCaudalServo(caudal);
	readIRSensor(IR_PIN1, IR_PIN2);
	//readIRSensor(IR_PIN1);   // USE FOR TESTING PURPOSES
}


/* INDIVIDUAL MOTOR FUNCTIONS */
void writeToCaudalServo(Servo servo){
	int pos=0;
	for(pos=0; pos<=180; pos+=180){
		servo.write(pos);
		delay(100);
	}
	for(pos=180; pos>=0; pos-=180){
		servo.write(pos);
		delay(100);
	}
}

void writeToPectoralServo(Servo right_servo, Servo left_servo){ // STILL NEED TO DETERMINE OPTIMAL MOTOR FREQUENCY 
	int pos=0;
	for(pos=0; pos<=180; pos+=180){
		left_servo.write(pos);
		delay(100);
	}
	for(pos=0; pos<=180; pos+=180){
		right_servo.write(pos);
		delay(100);
	}
}

void writeToDorsalServo(Servo servo){
	int pos = 0;
	for(pos = 0; pos <=180 ; pos +=180){
		servo.write(pos);
                delay(100);
	}
	for(pos=0; pos<=180; pos+=180){
		servo.write(pos);
	}
}

/* INDIVIDUAL IR FUNCTION */
void readIRSensor(int pin, int pin2){ // READ IR SENSOR 
	float volts = analogRead(pin)*0.0048828125; // trimming raw data(low) into voltage from signal
	float distance = 65*pow(volts, -1.10); // converting signal to distance
	float volts2 = analogRead(pin2)*0.0048828125;
	float distance2 = 65*pow(volts2, -1.10);
	Serial.println(distance);
	/*if(distance < 500 && distance2 < 500){
		
	}
        */
	delay(100);
}

/* void readIRSensor(int pin){
	float volts = analogRead(pin)*0.0048828125;
	float distance = 65*pow(volts, -1.10); 
	Serial.println(distance);
	delay(100);
}
*/

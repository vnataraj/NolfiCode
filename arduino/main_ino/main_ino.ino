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
int count=0;
bool distance2 = false;
bool up = false;
bool down = false;
float angles[3]; 

FreeSixIMU sixDOF = FreeSixIMU();

/* SETUP ROUTINE */

void setup(){
	sei();  // enable interrupts
	Serial.begin(9600);
        Wire.begin();
	pinMode(IR_PIN1, INPUT);
	pinMode(IR_PIN2, INPUT);
        Serial.println("Init 6DOF");
        sixDOF.init();
	PCintPort::attachInterrupt(IR_PIN1, &actOnDistance1, FALLING);
	PCintPort::attachInterrupt(IR_PIN2, actOnDistance2, FALLING);
	caudal.attach(CAUDAL_PIN);
        dorsal.attach(DORSAL_PIN);
        Serial.println("Init complete");
        pectoral1.attach(PECTORAL_LEFT_PIN);
        pectoral2.attach(PECTORAL_RIGHT_PIN);
	Serial.println("Okay, serial is instantiated");
}

/* FUNCTIONS CALLED BY INTERRUPTS */

void actOnDistance1(){
	distance1=true;
        //count++;
        //Serial.println("distance1");
}
void actOnDistance2(){
	distance2=true;
}

/* MAIN EXECUTION LOOP */
void loop(){
        int val1 = analogRead(IR_PIN1);
        int val2 = analogRead(IR_PIN2);
        
        //Serial.println(val2);
        
        if(val1>210 && val2>210){
          distance1=true;
          distance2=true;
        }
        //float volts = analogRead(IR_PIN1)*0.0048828125;
        //float distance = 65*pow(volts, -1.10); 
	//Serial.println(distance);
        //Serial.println("hello");
        /*
        sixDOF.getAngles(angles);
        Serial.print(angles[0]);
        Serial.print(" | ");
        Serial.print(angles[1]);
        Serial.print(" | ");
        Serial.print(angles[2]);
        Serial.println("");
        delay(5);
        */
	startServoRoutine();
        //dorsal.write(140);
        
       //caudal.write(140);
}

/* MOTOR FUNCTION */

void startServoRoutine(){
	if(distance1 && distance2){
		//turn right();  //dorsal
		writeToDorsalServo(dorsal);
                distance1=false;
                distance2=false;
                //Serial.println(count);
	}
        //caudal.write(0);
        //caudal.write(95);
        //writeToCaudalServo(caudal);
        writeToPectoralServo(pectoral1, pectoral2);
        writeToCaudalServo(caudal);
        //writeToPectoralServoTest(caudal);
        //writeToDorsalServo(dorsal);
	//readIRSensor(IR_PIN1, IR_PIN2);
	//readIRSensor(IR_PIN1);   // USE FOR TESTING PURPOSES
}


/* INDIVIDUAL MOTOR FUNCTIONS */
void writeToCaudalServo(Servo servo){
	int pos=16;
	for(pos=16; pos<=180; pos+=166){
		servo.write(pos);
		delay(200);
	}
	for(pos=180; pos>=16; pos-=166){
		servo.write(pos);
		delay(200);
	}
}

void writeToPectoralServoTest(Servo servo){
 sixDOF.getAngles(angles);
 Serial.println(angles[1]);
 if(angles[1]<328 && angles[1]>180){
   servo.write(180);
   Serial.println("up");
   delay(1000);
 }
 else if(angles[1]>53 && angles[1]<180){
  servo.write(0);
  Serial.println("down");
   delay(1000);
 }
 servo.write(90);
 delay(1000); 
}

void writeToPectoralServo(Servo right_servo, Servo left_servo){
        sixDOF.getAngles(angles); // STILL NEED TO DETERMINE OPTIMAL MOTOR FREQUENCY
        if(angles[1]<339 && angles[1]>180){
          left_servo.write(180);
          right_servo.write(0);
          delay(200);
        }
        else if(angles[1]>30 && angles[1]<180){
          left_servo.write(0);
          right_servo.write(180);
          delay(200);
        }
        else{
         left_servo.write(90);
         right_servo.write(90);
         delay(100); 
        }
        if(angles[2]<339 && angles[2]>180){
          left_servo.write(0);
          right_servo.write(0);
          delay(200);
        }
        else if(angles[2]>30 && angles[2]<180){
          left_servo.write(180);
          right_servo.write(180);
        }
        else{
         left_servo.write(90);
         right_servo.write(90);
         delay(100); 
        }
        //swriteToCaudalServo(caudal);
        
}

void writeToDorsalServo(Servo servo){
       servo.write(96);
       // inc by 22 degrees: max is 140!
	//int pos = 180;
	//servo.write(pos);
}

/* INDIVIDUAL IR FUNCTION */
/*
void readIRSensor(int pin, int pin2){ // READ IR SENSOR 
	float volts = analogRead(pin)*0.0048828125; // trimming raw data(low) into voltage from signal
	float distance = 65*pow(volts, -1.10); // converting signal to distance
	float volts2 = analogRead(pin2)*0.0048828125;
	float distance2 = 65*pow(volts2, -1.10);
	Serial.println(distance);
	/*if(distance < 500 && distance2 < 500){
		
	}
        /
	delay(100);
}
*/

/* void readIRSensor(int pin){
	float volts = analogRead(pin)*0.0048828125;
	float distance = 65*pow(volts, -1.10); 
	Serial.println(distance);
	delay(100);
}
*/

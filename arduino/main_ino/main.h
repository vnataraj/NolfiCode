#include <Servo.h>
#include <PinChangeInt.h>
#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Wire.h>


/* DEFINE PIN CONSTANTS HERE */

#define IR_PIN1				1 // IR sensor (1) signal pin
#define IR_PIN2				2
#define GYRO_PIN			3
#define FORCE_PIN			4
#define DORSAL_PIN			10
#define PECTORAL_LEFT_PIN	11
#define PECTORAL_RIGHT_PIN	12
#define CAUDAL_PIN			13 // caudal motor signal pin


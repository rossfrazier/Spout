//
//  Test.cpp
//  Spout
//
//  Implementation for the Test object (detailed description in the header file).

#include "Test.h"

void Test::controlPump(motorStatus_t pumpStatus) {
	if (pumpStatus == ON) {
		digitalWrite(Test::pumpTransistor, HIGH);
	}
	else if (pumpStatus == OFF) {
		digitalWrite(Test::pumpTransistor, LOW);
	}
}

void Test::runPumpForTime(int seconds) {
	controlPump(ON);
	delay(seconds*1000);
	controlPump(OFF);
}

//still needs code to control the motor -- analogWrite, probably.
void Test::controlConveyer(motorStatus_t motorStatus) {
	if (motorStatus == ON) {

	}
	else if (motorStatus == OFF) {

	}
}

void Test::runConveyerForTime(int seconds) {
	controlConveyer(ON);
	delay(seconds*1000);
	controlConveyer(OFF);
}

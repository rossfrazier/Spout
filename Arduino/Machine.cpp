//
//  Machine.cpp
//  Spout
//
//  Implementation for the Machine base object (detailed description in the header file).

#include "Machine.h"

Machine::Machine() {
}

const byte Machine::valveTransistorPins[]={6};

void Machine::setPins() {
  //setup pins as input/output; 
  pinMode(pumpTransistor, OUTPUT);
  for (byte i = 0; i < bottleCount(); i++) {
    pinMode(valveTransistorPins[i], OUTPUT);
  }
  Serial.println("pin mode selection complete");
}

byte Machine::bottleCount() {
  //sizeOf works for counting elements because it's an array of bytes
  return sizeof(valveTransistorPins);
}

void Machine::controlValve(valveStatus_t valveStatus, byte bottleNumber) {
  if (valveStatus==OPEN) {
    Serial.println("valve is open!");
    digitalWrite(valveTransistorPins[bottleNumber], HIGH);
  }
  else {
    Serial.println("valve is closed!");
    digitalWrite(valveTransistorPins[bottleNumber], LOW);
  }
}

void Machine::controlPump(motorStatus_t pumpStatus) {
  if (pumpStatus == ON) {
    Serial.println(pumpTransistor);
    Serial.println("pump is on!");
    digitalWrite(pumpTransistor, HIGH);
  }
  else if (pumpStatus == OFF) {
    Serial.println("pump is off!");
    digitalWrite(pumpTransistor, LOW);
  }
}

void Machine::runPumpForTime(int seconds) {
  controlPump(ON);
  delay(seconds*1000);
  controlPump(OFF);
}

void Machine::controlConveyer(motorStatus_t motorStatus) {
  if (motorStatus == ON) {

  }
  else if (motorStatus == OFF) {

  }
}

void Machine::runConveyerForTime(int seconds) {
  controlConveyer(ON);
  delay(seconds*1000);
  controlConveyer(OFF);
}

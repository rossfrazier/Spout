//
//  Machine.cpp
//  Spout
//
//  Implementation for the Machine base object (detailed description in the header file).

#include "Machine.h"

Machine::Machine() {
}

const byte Machine::valveTransistorPins[] = {6,5,8,9,3,4};
const byte Machine::pumpTransistor = 7;
const byte Machine::conveyerTransistor = 2;

//setup pins as input/output, and make sure they start at LOW
void Machine::setPins() {
  pinMode(pumpTransistor, OUTPUT);
  digitalWrite(pumpTransistor, LOW);
  for (byte i = 0; i < bottleCount(); i++) {
    pinMode(valveTransistorPins[i], OUTPUT);
    digitalWrite(valveTransistorPins[i], LOW);
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

void Machine::openValveForTime(byte bottleNumber, int milliseconds) {
  controlValve(OPEN,bottleNumber);
  Serial.println(milliseconds);
  delay(milliseconds);
  controlValve(CLOSE,bottleNumber);
}

void Machine::controlPump(motorStatus_t pumpStatus) {
  if (pumpStatus == ON) {
    Serial.println("pump is on!");
    digitalWrite(pumpTransistor, HIGH);
  }
  else if (pumpStatus == OFF) {
    Serial.println("pump is off!");
    digitalWrite(pumpTransistor, LOW);
  }
}

void Machine::runPumpForTime(int milliseconds) {
  controlPump(ON);
  delay(milliseconds);
  controlPump(OFF);
}

void Machine::controlConveyer(motorStatus_t motorStatus) {
  if (motorStatus == ON) {

  }
  else if (motorStatus == OFF) {

  }
}

void Machine::runConveyerForTime(int milliseconds) {
  controlConveyer(ON);
  delay(milliseconds);
  controlConveyer(OFF);
}

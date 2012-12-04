//
//  Machine.cpp
//  Spout
//
//  Implementation for the Machine base object (detailed description in the header file).

#include "Machine.h"

Machine::Machine() {
}

const byte Machine::valveTransistorPins[] = {3,4,5,6,8,9};

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
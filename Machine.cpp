//
//  Machine.cpp
//  Spout
//
//  Implementation for the Machine base object (detailed description in the header file).

#include "Machine.h"

Machine::Machine() : irSensor(0,100) {
}

const byte Machine::valveTransistorPins[] = {3,4,5,6,8,9};
const byte Machine::infraredSensorPin = 0;

//setup pins as input/output, and make sure they start at LOW (valves and sensors off)
void Machine::setPins() {
  pinMode(infraredSensorPin, OUTPUT);

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

bool Machine::isCupPresent() {
  if (irSensor.isCupPresent()) {
    Serial.println("Cup is present!");
  }
  else {
    Serial.println("Cup is not present...");
  }
  return irSensor.isCupPresent();
}

void Machine::recordIR() {
  irSensor.takeAndPushReading();
  long avg = irSensor.rollingAverage();
  Serial.print("machine rolling avg: ");
  Serial.print(avg);
  Serial.println();
}
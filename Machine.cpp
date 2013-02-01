//
//  Machine.cpp
//  Spout
//
//  Implementation for the Machine base object (detailed description in the header file).

#include "Machine.h"

Machine::Machine() {
}

const byte Machine::valveTransistorPins[] = {3,4,5,6,8,9};
const byte Machine::infraredSensorPin = 0;

//setup pins as input/output, and make sure they start at LOW (valves and sensors off)
void Machine::setPins() {
  pinMode(infraredSensorPin, OUTPUT);
  digitalWrite(infraredSensorPin, LOW);

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

// Sensor Methods
const int Machine::presentCupThreshold = 100;
const int Machine::defaultAverageReadingCount = 10;

//takes as many readings are specified and returns the average
int Machine::averageReading(int readingsCount) {
  int i, sumOfSensorValues;
  while (i < readingsCount) {
    sumOfSensorValues += analogRead(infraredSensorPin);
    i++;
    delay(1); //delay in between reads for stability
  }
  return sumOfSensorValues / readingsCount;
}


bool Machine::isCupPresent() {
  int latestAverageReading = averageReading(defaultAverageReadingCount);
  Serial.print("IR reading: ");
  Serial.print(latestAverageReading);
  Serial.println();
  if (latestAverageReading < presentCupThreshold) {
    return true;
  }
  return false;
}
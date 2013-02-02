//
//  IRSensor.cpp
//  Spout
//
//  Implementation for a class to manage the IR sensor

#include "IRSensor.h"

const int IRSensor::presentCupThreshold = 100;

IRSensor::IRSensor(byte pin, int readingsCount) : Queue(readingsCount) {
  _sensorPin = pin;
  _readingsCount = readingsCount;
}

void IRSensor::takeAndPushReadings() {
  for (int i = 0; i < _readingsCount; i++) {
    enqueue(analogRead(_sensorPin));
    delay(1);
  }
}

bool IRSensor::isCupPresent() {
  Serial.print("avg: ");
  Serial.print(rollingMean());
  Serial.println();

  if (rollingMean() <= presentCupThreshold) return true;
  return false;
}
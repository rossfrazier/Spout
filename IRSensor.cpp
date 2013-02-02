//
//  IRSensor.cpp
//  Spout
//
//  Implementation for a class to manage the IR sensor

#include "IRSensor.h"

const int IRSensor::presentCupThreshold = 100;

IRSensor::IRSensor(byte pin, int readingsCount) : Queue(readingsCount) {
  _sensorPin = pin;
}

void IRSensor::takeAndPushReading() {
  enqueue(analogRead(_sensorPin));
  delay(1);
}

long IRSensor::rollingAverage() {
  return mean();
}

long IRSensor::readingsSum() {
  return arraySum();
}

bool IRSensor::isCupPresent() {
  if (rollingAverage() <= presentCupThreshold) return true;
  return false;
}
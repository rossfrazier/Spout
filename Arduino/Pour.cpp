//
//  Pour.cpp
//  Spout
//
//  Implementation for the Pour object (detailed description in the header file).

#include "Pour.h"
#include "Drink.h"

//constructors and setters
Pour::Pour() {
  return;
}

Pour::Pour(byte bottle, int seconds) {
  setBottleAndSeconds(bottle, seconds);
}

//pouring action - open and closes valves after some amount of time
void Pour::doPour() {
  if (bottle() && seconds()) {
    controlValve(OPEN, bottle());
    delay(milliseconds());
    controlValve(CLOSE, bottle());
  }
}

//state getters
byte Pour::bottle() {
  return _bottle;
}

int Pour::seconds() {
  return _seconds;
}

int Pour::milliseconds() {
  return _seconds*1000;
}

//state setters
void Pour::setBottleAndSeconds(byte bottle, int seconds) {
  _bottle = bottle;
  _seconds = seconds;
}

void Pour::setBottle(byte bottle) {
  _bottle = bottle;
}

void Pour::setSeconds(int seconds) {
  _seconds = seconds;
}

//private methods
void Pour::controlValve(valveStatus_t valveStatus, byte bottleNumber) {
  if (valveStatus==OPEN) {
    Serial.println("valve is open!");
    digitalWrite(Drink::valveTransistorPins[bottleNumber], HIGH);
  }
  else {
    Serial.println("valve is closed!");
    digitalWrite(Drink::valveTransistorPins[bottleNumber], LOW);
  }
}

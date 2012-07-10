//
//  Pour.cpp
//  Spout
//
//  Implementation for the Pour object (detailed description in the header file).

#include "Pour.h"

//constructors and setters
Pour::Pour() {
  return;
}

Pour::Pour(byte bottle, int seconds) {
  setBottleAndSeconds(bottle, seconds);
}

//pouring action - open and closes valves after some amount of time
//returns true if successful. invoked by the drink object.
bool Pour::doPour() {
  highestPossibleBottleIndex = bottleCount()-1;
  lowestPossibleBottleIndex = 0;
  if (bottle()>=lowestPossibleBottleIndex && bottle()<=highestPossibleBottleIndex && seconds()) {
    controlValve(OPEN, bottle());
    delay(milliseconds());
    controlValve(CLOSE, bottle());
    return true;
  }
  return false;
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
  setBottle(bottle);
  setSeconds(seconds);
}

void Pour::setBottle(byte bottle) {
  _bottle = bottle;
}

void Pour::setSeconds(int seconds) {
  _seconds = seconds;
}

//
//  Pour.cpp
//  Spout
//
//  Implementation for the Pour object (detailed description in the header file).

#include "Pour.h"

Pour::Pour() {
    return;
}

Pour::Pour(byte bottle, int seconds) {
	setBottleAndSeconds(bottle, seconds);
}

byte Pour::bottle() {
	return _bottle;
}

int Pour::seconds() {
	return _seconds;
}

int Pour::milliseconds() {
	return _seconds*1000;
}

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

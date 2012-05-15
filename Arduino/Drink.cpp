//
//  Drink.cpp
//  Spout
//
//  Implementation for the Drink object (detailed description in the header file).

#include "Drink.h"

//if valveTransistorPins[]={8,2}, then the first bottle is on transistor pin 8, and the second one is on transistor pin 2
const byte Drink::valveTransistorPins[]={8};

// this is an object constructor. it sets the object's initial state.
Drink::Drink(Pour * pours, byte numberOfPours) {
    setPouring(false);
    setComplete(false);
    _allPours = pours;
    _numberOfPours = numberOfPours;
}

bool Drink::isPouring() {
    return _isPouring;
}

bool Drink::isComplete() {
    return _isComplete;
}

byte Drink::numberOfPours() {
    return _numberOfPours;
}

//loops through all pour instructions
void Drink::beginPouring() {
    for (byte i = 0; i < numberOfPours(); i++) {
        doPour(_allPours[i]);
    }
    setPouringComplete(true);
}

//instructions for an individual pour. this is where opening/closing valves go.
void Drink::doPour(Pour pour) {
    //opening and closing valve using pour.bottle(), and an amount of time (e.g. pour.milliseconds())
    controlValve(OPEN,pour.bottle());
    delay(pour.milliseconds());
    controlValve(CLOSE,pour.bottle());
}

//private methods (can't be called from outside this file)
void Drink::controlValve(valveStatus_t shouldValveOpen, byte bottleNumber) {
    setPouring(shouldValveOpen);
    if (shouldValveOpen) {
        Serial.println("valve is open!");
        digitalWrite(valveTransistorPins[bottleNumber], HIGH);
    }
    else {
        Serial.println("valve is closed!");
        digitalWrite(valveTransistorPins[bottleNumber], LOW);
    }
}

void Drink::setPouring(bool isPouring) {
    _isPouring = isPouring;
}

void Drink::setComplete(bool complete) {
    _isComplete = complete;
}

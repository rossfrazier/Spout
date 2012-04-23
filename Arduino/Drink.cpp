//
//  Drink.cpp
//  Spout
//
//  Implementation for the Drink object (detailed description in the header file).

#include "Drink.h"

const byte Drink::valveTransistorPins[]={8};

// this is an object constructor. it sets the object's initial state.
Drink::Drink(Pour * pours, byte numberOfPours) {
    setPouring(false);
    _numberOfPours = numberOfPours;
    _allPours = pours;
}

bool Drink::isPouring() {
    return _isPouring;
}

bool Drink::isPouringComplete() {
    return _isPouringComplete;
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
    //opening and closing valve using pour.bottle(), and pour.seconds() or pour.milliseconds()
    controlValve(true,pour.bottle());
    Serial.println(pour.seconds());
    Serial.println(pour.milliseconds());
    delay(pour.milliseconds());
    controlValve(false,pour.bottle());
}

void Drink::controlValve(bool shouldValveOpen, byte bottleNumber) {
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

//private methods (can't be called from outside this file)
void Drink::setPouring(bool isPouring) {
    _isPouring = isPouring;
}

void Drink::setPouringComplete(bool complete) {
    _isPouringComplete = complete;
}

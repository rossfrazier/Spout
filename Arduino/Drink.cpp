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
    _allPours = pours;
    _numberOfPours = numberOfPours;
}

//state getters
bool Drink::isComplete() {
    return _isComplete;
}

byte Drink::numberOfPours() {
    return _numberOfPours;
}

//loops through all pour instructions
void Drink::beginPouring() {
    for (byte i = 0; i < numberOfPours(); i++) {
        _allPours[i].doPour();
    }
    setComplete(true);
}

//private methods (can't be called from outside this file)
//state setters
void Drink::setComplete(bool complete) {
    _isComplete = complete;
}

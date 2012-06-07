//
//  Drink.cpp
//  Spout
//
//  Implementation for the Drink object (detailed description in the header file).

#include "Drink.h"

// this is an object constructor. it sets the object's initial state.
Drink::Drink(Pour * pours, byte numberOfPours) {
  _isComplete = false;
  _allPours = pours;
  _numberOfPours = numberOfPours;
}

//destructor-- actually not sure if this is deallocing the same object array twice
Drink::~Drink() {
  delete _allPours;
}

//object state
byte Drink::numberOfPours() {
  return _numberOfPours;
}

bool Drink::isComplete() {
  return _isComplete;
}

//loops through all pour instructions
void Drink::beginPouring() {
  //validation (_isComplete is false by default)
  if (numberOfPours() > bottleCount()) return;

  for (byte i = 0; i < numberOfPours(); i++) {
    // if doPour returns false, end early and don't set as complete
    if (!_allPours[i].doPour()) return;
  }
  setComplete(true);
}

//private methods (can't be called from outside this file)
//state setters
void Drink::setComplete(bool complete) {
  _isComplete = complete;
}

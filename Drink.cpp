//
//  Drink.cpp
//  Spout
//
//  Implementation for the Drink object (detailed description in the header file).

#include "Drink.h"

// this is an object constructor. it sets the object's initial state.
Drink::Drink(Pour * allPours, byte numberOfPours) {
  _isComplete = false;
  _numberOfPours = numberOfPours;
  _allPours = allPours;
}

//loops through all pour instructions. sets drink as complete only if successful
void Drink::beginPouring() {
  //validation (_isComplete is false by default)
  if (numberOfPours() > bottleCount()) return;
  
  if (isCupPresent()) {
    for (byte i = 0; i < numberOfPours(); i++) {
      // if doPour returns false, end early and don't set as complete
      if (!_allPours[i].doPour()) return;
    }
    setComplete(true);
  }
  else {
    //if cup isn't there, run this method again (which loops until there's a cup)
    beginPouring();   
  }
}

//object state
byte Drink::numberOfPours() {
  return _numberOfPours;
}

bool Drink::isComplete() {
  return _isComplete;
}

//private methods (can't be called from outside this file)
//state setters
void Drink::setComplete(bool complete) {
  _isComplete = complete;
}

//
//  Drink.h
//  Spout
//
//  Interface (description of the object) for the Drink object (the finished drink, which is the 
//  collection of all its pours). Includes a pointer to an array of pour information, and a method
//  that goes through each pour object and tells the machine to pour it. This is where validations
//  go, and the drink object is what passes back to the main function whether the request was a
//  success or a failure.
//
//  A Drink has many Pours.  A Pour belongs to a Drink.

#ifndef Spout_Drink_h
#define Spout_Drink_h

#include "Machine.h"
#include "Pour.h"

class Drink: private Machine {
  public:
    //constructor
    Drink(Pour * allPours, byte numberOfPours);

    //state getters
    byte numberOfPours();
    bool isComplete();

    //instance variable: pointer to an array of pour objects created during the request function
    Pour * _allPours;

    //loops through collection of pour objects. sets drink as complete only if successful
    void beginPouring();
      
  private:
    byte _numberOfPours;

    //setters and instance variables
    //has the complete collection of pour objects finished pouring?
    //this would remain false due to a validation error, for example
    void setComplete(bool complete);
    bool _isComplete;     
};

#endif

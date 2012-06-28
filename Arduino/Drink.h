//
//  Drink.h
//  Spout
//
//  Interface (description of the object) for the Drink object (the finished drink, which is the 
//  sum of all its pours). Includes an array of pour information, and a variable to check whether
//  it's in the process of pouring or not. The functions that open the valves, time their closing
//  and move the cup or carousel will go in this section.
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

    //collection of pour objects
    Pour * _allPours;

    //loops through collection of pour objects
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

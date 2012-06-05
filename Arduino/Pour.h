//
//  Pour.h
//  Spout
//
//  Implementation for the Pour object. Includes pour info and the action itself.
//  A pour consists of a bottle's position and the time the valve should stay open. 
//
//  A Drink has many Pours. A Pour belongs to a Drink.

#ifndef Spout_Pour_h
#define Spout_Pour_h

#include "Machine.h"

class Pour: private Machine {
  public:
    //constructors
    Pour();
    Pour(byte bottle, int seconds);

    //pouring action
    bool doPour();
    
    //state setters
    void setBottle(byte bottle);
    void setSeconds(int seconds);
    void setBottleAndSeconds(byte bottle, int seconds);
    
    //state getters
    byte bottle();
    int seconds();
    int milliseconds();
  
  private:
    //instance variables
    byte _bottle;
    int _seconds;
};

#endif

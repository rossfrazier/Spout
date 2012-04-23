//
//  Pour.h
//  Spout
//
//  Implementation for the Pour object. Very simple right now, but we can add detail if needed.
//  A pour consists of a bottle's position and the time the valve should stay open. 
//
//  A Drink has many Pours. A Pour belongs to a Drink.

#ifndef Spout_Pour_h
#define Spout_Pour_h

#include "SPI.h"

class Pour {
    public:
        Pour();
        Pour(byte bottle, int seconds);
        
        byte bottle();
        void setBottle(byte bottle);
        
        int seconds();
        int milliseconds();
        void setSeconds(int seconds);
    
        void setBottleAndSeconds(byte bottle, int seconds);
    
    private:
        byte _bottle;
        int _seconds;
};

#endif

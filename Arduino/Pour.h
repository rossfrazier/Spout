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

#include "SPI.h"

class Pour {
    public:
        //constructors
        Pour();
        Pour(byte bottle, int seconds);

        //pouring action
        void doPour();
        
        //state setters
        void setBottle(byte bottle);
        void setSeconds(int seconds);
        void setBottleAndSeconds(byte bottle, int seconds);
        
        //state getters
        byte bottle();
        int seconds();
        int milliseconds();
    
    private:
        enum valveStatus_t {
            OPEN,
            CLOSE
        };
        static void controlValve(valveStatus_t valveStatus, byte bottleNumber);

        //instance variables
        byte _bottle;
        int _seconds;
};

#endif

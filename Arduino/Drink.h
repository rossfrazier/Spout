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

#include "SPI.h"
#include "Pour.h"

class Drink {
    public:
        Drink(Pour * pours, byte numberOfPours);
    
        bool isPouring();
        bool isPouringComplete();
    
        byte numberOfPours();
    
        void beginPouring();
        void doPour(Pour pour);
        void controlValve(bool shouldValveOpen, byte bottleNumber);

        /* Stores digitial IO pin information for n number of valve transistors
         * example: valveTransistorPins[0] = 10
         * Static means it is compiled once but can be accessed over and over
         * Const means it can't be modified by the program. */
        static const byte valveTransistorPins[];
        
    private:
        void setPouring(bool isPouring);
        bool _isPouring;
    
        void setPouringComplete(bool complete);
        bool _isPouringComplete;
        
        byte _numberOfPours;
        Pour * _allPours;
};

#endif

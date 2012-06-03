//
//  Test.h
//  Spout
//
//  Implementation for the Test object. These are a series of methods 
//  that can be easily used to control the pump and some of the valves.

#ifndef Spout_Test_h
#define Spout_Test_h

#include "SPI.h"

class Test {
   public:
     //constructors
     Test();

     enum motorStatus_t {
       ON,
       OFF
     }
     static void controlPump(motorStatus_t pumpStatus);
     static void runPumpForTime(int seconds);

     static void controlConveyer(motorStatus_t motorStatus);
     static void runConveyerForTime(int seconds);

   private:
      //transistor pins for motors and pumps
      static const byte pumpTransistor = 1;
      static const byte conveyerTransistor = 2;
};

#endif

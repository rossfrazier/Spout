//
//  Machine.h
//  Spout
//
//  Base class for other objects related to pouring drinks 
//  (likely most if not all other objects). Holds all methods
//  that raise or lower voltage on the Arduino board (pumps,
//  valves, and motors)

#ifndef Spout_Machine_h
#define Spout_Machine_h

#include "SPI.h"

class Machine {
  public:
    //constructors
    Machine();

    //PIN SETUP, DATA, AND HELPER METHODS
    static void setPins();
    static byte bottleCount(); //length of valveTransistorPin array

    //these are only needed as public for testing
    void runPumpForTime(int seconds);
    void runConveyerForTime(int seconds);

  protected:
    /* Stores digitial IO pin information
    * example: valveTransistorPins[0] = 10
    * Static means it is compiled once but can be accessed over and over
    * Const means it can't be modified by the program. */
    static const byte valveTransistorPins[];
    static const byte pumpTransistor;
    static const byte conveyerTransistor;

    // MACHINE OPERATION
    // valve operation
    enum valveStatus_t {
      OPEN,
      CLOSE
    };
    void controlValve(valveStatus_t valveStatus, byte bottleNumber);

    //pump and conveyer operation
    enum motorStatus_t {
      ON,
      OFF
    };
    void controlPump(motorStatus_t pumpStatus);
    void controlConveyer(motorStatus_t motorStatus);  
};

#endif

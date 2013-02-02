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
#include "IRSensor.h"

class Machine {
  public:
    //constructors
    Machine();

    //PIN SETUP, DATA, AND HELPER METHODS
    static void setPins(); //set pinModes and make sure all pins start digital written to LOW
    static byte bottleCount(); //length of valveTransistorPin array

    //IR sensor
    static bool isCupPresent(); //runs sensor n times and uses running avg to find if there's a cup

  protected:
    /* Stores digitial IO pin information
    * example: valveTransistorPins[0] = 10
    * Static means it is compiled once but can be accessed over and over
    * Const means it can't be modified by the program. */
    static const byte valveTransistorPins[];
    static const byte infraredSensorPin;

    // MACHINE OPERATION
    // valve operation
    enum valveStatus_t {
      OPEN,
      CLOSE
    };
    void controlValve(valveStatus_t valveStatus, byte bottleNumber);

};

#endif

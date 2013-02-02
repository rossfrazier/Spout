//
//  IRSensor.h
//  Spout
//
//  A subclass of a FIFO queue used to manage readings from IR sensor

#ifndef Spout_IRSensor_h
#define Spout_IRSensor_h

#include "SPI.h"
#include "Queue.h"

class IRSensor : private Queue {
  public:
    IRSensor(byte pin, int readingsCount);

    void takeAndPushReading();
    long rollingAverage();
    bool isCupPresent();
    long readingsSum();

  private:
    static const int presentCupThreshold;
    byte _sensorPin;
};

#endif
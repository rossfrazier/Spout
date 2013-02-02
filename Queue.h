//
//  Queue.h
//  Spout
//
//  A first-in, first-out queue, probably used to keep running
//  averages of readings from IR sensors.

#ifndef Spout_Queue_h
#define Spout_Queue_h

#include "SPI.h"

class Queue {
  public:
    //constructor/destructor
    Queue(int capacity);
    ~Queue();

    void enqueue(int element);
    void dequeue();
    bool isEmpty();
    long arraySum();
    long mean();

  private:
    int _capacity;
    int _size;
    int _front;
    int _back;
    int * _elements;
};

#endif
//
//  Queue.cpp
//  Spout
//
//  Implementation for a generic FIFO queue

#include "Queue.h"

// this is an object constructor. it sets the object's initial state.
Queue::Queue(int capacity) {
  _capacity = 100;
  _size = 0;
  _front = 0;
  _back = -1;
  _elements = new int [capacity];
}

Queue::~Queue() {
  delete[] _elements;
}

void Queue::enqueue(int element) {
  Serial.print("reading : ");
  Serial.print(element);
  Serial.println();

  if (_size == _capacity) dequeue();
  _size++;
  _back++;
  if (_back == _capacity) _back = 0;
  _elements[_back] = element;
  return;
}

void Queue::dequeue() {
  if (_size == 0) return;
  _size--;
  _front++;
  if (_front == _size) _front = 0;
  return;
}

bool Queue::isEmpty() {
  if (_size == 0) return true;
  return false;
}

long Queue::arraySum() {
  if (_size < 100) return 0;
  long queueSum;
  queueSum = 0;
  for (int i = _front; i <= _back; i++) {
    queueSum += _elements[i];
  }
  Serial.print("function sum: ");
  Serial.print(queueSum);
  Serial.println();
  return queueSum;
}

long Queue::mean() {
  if (_size < 100) return 0;

  Serial.print("sum: ");
  Serial.print(arraySum());
  Serial.println();

  long arrayMean = arraySum() / 100;

  Serial.print("mean: ");
  Serial.print(arrayMean);
  Serial.println();

  return arrayMean;
}
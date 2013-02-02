//
//  Queue.cpp
//  Spout
//
//  Implementation for a generic FIFO queue

#include "Queue.h"

// this is an object constructor. it sets the object's initial state.
Queue::Queue(int capacity) {
  _capacity = capacity;
  _size = 0;
  _front = 0;
  _back = -1;
  _elements = new int [capacity];
}

Queue::~Queue() {
  delete[] _elements;
}

void Queue::enqueue(int element) {
  if (_size == _capacity) dequeue();
  _size++;
  _back++;
  if (_back == _capacity) _back = 0;
  _elements[_back] = element;
  _sum += element;
  return;
}

void Queue::dequeue() {
  if (isEmpty()) return;
  _sum -= _elements[_front];
  _size--;
  _front++;
  if (_front == _capacity) _front = 0;
  return;
}

bool Queue::isEmpty() {
  if (_size == 0) return true;
  return false;
}

long Queue::getSum() {
  return _sum;
}

long Queue::rollingMean() {
  long arrayMean = getSum() / _size;
  return arrayMean;
}
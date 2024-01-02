#include "lock.h"

#include <Arduino.h>

#define LOCKER_PIN 23

Lock::Lock() {}
Lock::~Lock() {}
void Lock::begin() { this->servo.attach(LOCKER_PIN); }
void Lock::open() { this->servo.write(0); }
void Lock::close() { this->servo.write(90); }

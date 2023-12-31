#ifndef LOCKER_H
#define LOCKER_H

#define LOCKER_PIN 23

#include <ESP32Servo.h> //Kevin Harrington,John K. Bennett

class Lock {
public:
  Lock() { this->servo.attach(LOCKER_PIN); }
  ~Lock(){};

  void open() { this->servo.write(0); }
  void close() { this->servo.write(90); }

private:
  Servo servo;
};

#endif // !DEBUG

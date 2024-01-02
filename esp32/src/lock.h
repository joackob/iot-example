#ifndef LOCKER_H
#define LOCKER_H

#include <ESP32Servo.h>  //Kevin Harrington,John K. Bennett

class Lock {
 public:
  Lock();
  ~Lock();
  void begin();
  void open();
  void close();

 private:
  Servo servo;
};

#endif  // !DEBUG

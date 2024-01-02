#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger {
 public:
  Logger();
  ~Logger();
  void begin();
  void log(const char *message);
  void log(String message);

 private:
};

#endif  // !DEBUG

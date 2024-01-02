#include "logger.h"

#define RATE_IN_BITS_PER_SECOND 9600

Logger::Logger() {}
Logger::~Logger() {}

void Logger::begin() {
  Serial.begin(RATE_IN_BITS_PER_SECOND);
  delay(10);
}

void Logger::log(const char *message) { Serial.println(message); }

void Logger::log(String message) { Serial.println(message); }

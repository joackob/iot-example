#include "indicator.h"

#include <Arduino.h>

#define INDICATOR_PIN 2
#define INDICATOR_DELAY 100

LedIndicator::LedIndicator() {}
LedIndicator::~LedIndicator() {}

void LedIndicator::begin() { pinMode(INDICATOR_PIN, OUTPUT); }

void LedIndicator::blink() {
  digitalWrite(INDICATOR_PIN, HIGH);
  delay(INDICATOR_DELAY);
  digitalWrite(INDICATOR_PIN, LOW);
  delay(INDICATOR_DELAY);
}

void LedIndicator::on() { digitalWrite(INDICATOR_PIN, HIGH); }

void LedIndicator::off() { digitalWrite(INDICATOR_PIN, LOW); }

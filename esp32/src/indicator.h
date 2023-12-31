#ifndef INDICATOR_H
#define INDICATOR_H

#define INDICATOR_PIN 2
#define INDICATOR_DELAY 100

class LedIndicator {
public:
  LedIndicator() { pinMode(INDICATOR_PIN, OUTPUT); }
  ~LedIndicator() {}

  void blink() {
    digitalWrite(INDICATOR_PIN, HIGH);
    delay(INDICATOR_DELAY);
    digitalWrite(INDICATOR_PIN, LOW);
    delay(INDICATOR_DELAY);
  }
  void on() { digitalWrite(INDICATOR_PIN, HIGH); }
  void off() { digitalWrite(INDICATOR_PIN, LOW); }

private:
};

#endif // !DEBUG

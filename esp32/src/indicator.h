#ifndef INDICATOR_H
#define INDICATOR_H

class LedIndicator {
 public:
  LedIndicator();
  ~LedIndicator();
  void begin();
  void blink();
  void on();
  void off();

 private:
};

#endif  // !DEBUG

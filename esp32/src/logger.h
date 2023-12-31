#ifndef LOGGER_H
#define LOGGER_H

#define RATE_IN_BITS_PER_SECOND 115200

#include "../wifi_config.h"

class Logger
{
public:
  Logger() { Serial.begin(RATE_IN_BITS_PER_SECOND); }
  ~Logger(){};

  void log(String message)
  {
    Serial.println();
    Serial.println(message);
  }
  void logSSIDWifiToConnect()
  {
    this->log(String("Connecting to ") + String(WIFI_SSID));
  }

  void logLocalIPWifi(IPAddress localIP)
  {
    this->log(String("Wifi connected with IP addresss ") + String(localIP));
  }

  void logTopicAndMessage(String topic, String message)
  {
    this->log(String("Topic: ") + topic + String(" Message: ") + message);
  }

private:
};

#endif // !DEBUG

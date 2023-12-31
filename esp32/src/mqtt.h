#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h> //Nick O'Leary
#include <WiFi.h>
#include <stdint.h>

#include "../mqtt_config.h"
#include "../wifi_config.h"

#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "ESP32"

typedef void (*OnWifiConnectingCallback)();
typedef void (*OnWifiConnectedCallback)();
typedef void (*OnMQTTDisconnectedCallback)();
typedef void (*OnMQTTConnectedCallback)();
typedef void (*OnMessageCallback)(String, String);

class MQTT
{
public:
  MQTT() : channel(this->wifi){};
  MQTT(const MQTT &other) : wifi(other.wifi), channel(other.channel) {}
  MQTT(MQTT &&other) : wifi(other.wifi), channel(other.channel) {}
  ~MQTT(){};

  MQTT &operator=(const MQTT &other)
  {
    this->wifi = other.wifi;
    this->channel = other.channel;
  };

  void operator()(char *t, uint8_t *m, unsigned l) const
  {
    String topic = String(t);
    String message;
    for (int i = 0; i < l; i++)
    {
      message += (char)m[i];
    }
    this->onMessageCallback(topic, message);
  }

  MQTT &onWifiConnecting(OnWifiConnectingCallback callback)
  {
    this->onWifiConnectingCallback = callback;
    return *this;
  }

  MQTT &onWifiConnected(OnWifiConnectedCallback callback)
  {
    this->onWifiConnectedCallback = callback;
    return *this;
  }

  MQTT &onMQTTDisconnected(OnMQTTDisconnectedCallback callback)
  {
    this->onMQTTDisconnectedCallback = callback;
    return *this;
  }

  MQTT &onMQTTConnected(OnMQTTConnectedCallback callback)
  {
    this->onMQTTConnectedCallback = callback;
    return *this;
  }

  MQTT &onMessage(OnMessageCallback callback)
  {
    this->onMessageCallback = callback;
    return *this;
  }

  MQTT &build()
  {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
      this->onWifiConnectingCallback();
    }
    this->onWifiConnectedCallback();
    this->channel.setServer(MQTT_HOST, MQTT_PORT);
    this->channel.setCallback(*this);
    return *this;
  };

  void loop()
  {
    while (!this->channel.connected())
    {
      if (this->channel.connect(MQTT_CLIENT_ID))
      {
        this->channel.subscribe(MQTT_TOPIC);
      }
      else
      {
        this->onMQTTDisconnectedCallback();
      }
    }
    this->channel.loop();
  };

private:
  WiFiClient wifi;
  PubSubClient channel;
  OnWifiConnectingCallback onWifiConnectingCallback;
  OnWifiConnectedCallback onWifiConnectedCallback;
  OnMQTTDisconnectedCallback onMQTTDisconnectedCallback;
  OnMQTTConnectedCallback onMQTTConnectedCallback;
  OnMessageCallback onMessageCallback;
};

#endif // !MQTT_H

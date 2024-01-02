#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h> //Nick O'Leary
#include <WiFi.h>
#include <stdint.h>

typedef void (*OnWifiConnectingCallback)(const char *ssid_wifi);
typedef void (*OnWifiConnectedCallback)(const char *local_ip);
typedef void (*OnMQTTDisconnectedCallback)(int mqtt_error_code);
typedef void (*OnMQTTConnectedCallback)(const char *broker_host,
                                        uint16_t broker_port);
typedef void (*OnMQTTConnectingCallback)();
typedef void (*OnMessageCallback)(char *topic, uint8_t *message,
                                  unsigned int long_message);

class MQTT {
public:
  MQTT();
  MQTT(const MQTT &other);
  MQTT(MQTT &&other);
  ~MQTT();
  MQTT &operator=(const MQTT &other);
  MQTT &onWifiConnecting(OnWifiConnectingCallback callback);
  MQTT &onWifiConnected(OnWifiConnectedCallback callback);
  MQTT &onMQTTDisconnected(OnMQTTDisconnectedCallback callback);
  MQTT &onMQTTConnected(OnMQTTConnectedCallback callback);
  MQTT &onMQTTConnecting(OnMQTTConnectingCallback callback);
  MQTT &onMessage(OnMessageCallback callback);
  MQTT &build();
  void loop();

private:
  WiFiClient wifi;
  PubSubClient socket;
  OnWifiConnectingCallback onWifiConnectingCallback;
  OnWifiConnectedCallback onWifiConnectedCallback;
  OnMQTTDisconnectedCallback onMQTTDisconnectedCallback;
  OnMQTTConnectedCallback onMQTTConnectedCallback;
  OnMQTTConnectingCallback onMQTTConnectingCallback;
  OnMessageCallback onMessageCallback;
};

#endif // !MQTT_H

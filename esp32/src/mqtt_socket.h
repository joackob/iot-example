#ifndef MQTT_SOCKET_H
#define MQTT_SOCKET_H

#include <PubSubClient.h>  //Nick O'Leary
#include <WiFi.h>
#include <stdint.h>

typedef void (*OnWifiConnectingCallback)(const char *ssid_wifi);
typedef void (*OnWifiConnectedCallback)(const char *local_ip);
typedef void (*OnMQTTDisconnectedCallback)(int mqtt_error_code);
typedef void (*OnMQTTConnectedCallback)(const char *broker_host,
                                        uint16_t broker_port);
typedef void (*OnMQTTConnectingCallback)();
typedef void (*OnMessageCallback)(char *topic, uint8_t *message,
                                  unsigned int length_message);

class MQTTSocket {
 public:
  MQTTSocket();
  MQTTSocket(const MQTTSocket &other);
  MQTTSocket(MQTTSocket &&other);
  ~MQTTSocket();
  MQTTSocket &operator=(const MQTTSocket &other);
  MQTTSocket &onWifiConnecting(OnWifiConnectingCallback callback);
  MQTTSocket &onWifiConnected(OnWifiConnectedCallback callback);
  MQTTSocket &onMQTTDisconnected(OnMQTTDisconnectedCallback callback);
  MQTTSocket &onMQTTConnected(OnMQTTConnectedCallback callback);
  MQTTSocket &onMQTTConnecting(OnMQTTConnectingCallback callback);
  MQTTSocket &onMessage(OnMessageCallback callback);
  MQTTSocket &build();
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

#endif

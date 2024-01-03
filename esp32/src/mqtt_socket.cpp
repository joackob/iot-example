#include "mqtt_socket.h"

#include "../mqtt_config.h"
#include "../wifi_config.h"

#define MQTT_CLIENT_ID "ESP32"

MQTTSocket::MQTTSocket() {
  this->socket.setClient(this->wifi);
  this->onWifiConnectingCallback = nullptr;
  this->onWifiConnectedCallback = nullptr;
  this->onMQTTConnectedCallback = nullptr;
  this->onMQTTDisconnectedCallback = nullptr;
  this->onMQTTConnectingCallback = nullptr;
}

MQTTSocket::MQTTSocket(const MQTTSocket &other)
    : wifi(other.wifi), socket(other.socket) {}

MQTTSocket::MQTTSocket(MQTTSocket &&other)
    : wifi(other.wifi), socket(other.socket) {}

MQTTSocket::~MQTTSocket(){};

MQTTSocket &MQTTSocket::operator=(const MQTTSocket &other) {
  this->wifi = other.wifi;
  this->socket = other.socket;
  return *this;
};

MQTTSocket &MQTTSocket::onWifiConnecting(OnWifiConnectingCallback callback) {
  this->onWifiConnectingCallback = callback;
  return *this;
}

MQTTSocket &MQTTSocket::onWifiConnected(OnWifiConnectedCallback callback) {
  this->onWifiConnectedCallback = callback;
  return *this;
}

MQTTSocket &MQTTSocket::onMQTTDisconnected(
    OnMQTTDisconnectedCallback callback) {
  this->onMQTTDisconnectedCallback = callback;
  return *this;
}

MQTTSocket &MQTTSocket::onMQTTConnected(OnMQTTConnectedCallback callback) {
  this->onMQTTConnectedCallback = callback;
  return *this;
}

MQTTSocket &MQTTSocket::onMQTTConnecting(OnMQTTConnectingCallback callback) {
  this->onMQTTConnectingCallback = callback;
  return *this;
}

MQTTSocket &MQTTSocket::onMessage(OnMessageCallback callback) {
  this->onMessageCallback = callback;
  return *this;
}

MQTTSocket &MQTTSocket::build() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    this->onWifiConnectingCallback(WIFI_SSID);
  }
  this->onWifiConnectedCallback(WiFi.localIP().toString().c_str());
  this->socket.setServer(MQTT_HOST, MQTT_PORT);
  this->socket.setCallback(this->onMessageCallback);
  return *this;
};

void MQTTSocket::loop() {
  while (!this->socket.connected()) {
    if (this->socket.connect(MQTT_CLIENT_ID)) {
      this->socket.subscribe(MQTT_TOPIC);
      this->onMQTTConnectedCallback(MQTT_HOST, MQTT_PORT);
    } else {
      this->onMQTTDisconnectedCallback(this->socket.state());
    }
  }
  this->socket.loop();
};

#include "mqtt.h"

#include "../mqtt_config.h"
#include "../wifi_config.h"

#define MQTT_CLIENT_ID "ESP32"

MQTT::MQTT() {
  this->channel.setClient(this->wifi);
  this->onWifiConnectingCallback = nullptr;
  this->onWifiConnectedCallback = nullptr;
  this->onMQTTConnectedCallback = nullptr;
  this->onMQTTDisconnectedCallback = nullptr;
  this->onMQTTConnectingCallback = nullptr;
}

MQTT::MQTT(const MQTT &other) : wifi(other.wifi), channel(other.channel) {}

MQTT::MQTT(MQTT &&other) : wifi(other.wifi), channel(other.channel) {}

MQTT::~MQTT(){};

MQTT &MQTT::operator=(const MQTT &other) {
  this->wifi = other.wifi;
  this->channel = other.channel;
  return *this;
};

MQTT &MQTT::onWifiConnecting(OnWifiConnectingCallback callback) {
  this->onWifiConnectingCallback = callback;
  return *this;
}

MQTT &MQTT::onWifiConnected(OnWifiConnectedCallback callback) {
  this->onWifiConnectedCallback = callback;
  return *this;
}

MQTT &MQTT::onMQTTDisconnected(OnMQTTDisconnectedCallback callback) {
  this->onMQTTDisconnectedCallback = callback;
  return *this;
}

MQTT &MQTT::onMQTTConnected(OnMQTTConnectedCallback callback) {
  this->onMQTTConnectedCallback = callback;
  return *this;
}

MQTT &MQTT::onMQTTConnecting(OnMQTTConnectingCallback callback) {
  this->onMQTTConnectingCallback = callback;
  return *this;
}

MQTT &MQTT::onMessage(OnMessageCallback callback) {
  this->onMessageCallback = callback;
  return *this;
}

MQTT &MQTT::build() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    this->onWifiConnectingCallback(WIFI_SSID);
  }
  this->onWifiConnectedCallback(WiFi.localIP().toString().c_str());
  this->channel.setServer(MQTT_HOST, MQTT_PORT);
  this->channel.setCallback(this->onMessageCallback);
  return *this;
};

void MQTT::loop() {
  while (!this->channel.connected()) {
    if (this->channel.connect(MQTT_CLIENT_ID)) {
      this->channel.subscribe(MQTT_TOPIC);
      this->onMQTTConnectedCallback(MQTT_HOST, MQTT_PORT);
    } else {
      this->onMQTTDisconnectedCallback(this->channel.state());
    }
  }
  this->channel.loop();
};

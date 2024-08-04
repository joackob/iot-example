// settings
#include "mqtt_config.h"

// src
#include "./src/indicator.h"
#include "./src/lock.h"
#include "./src/logger.h"
#include "./src/mqtt_socket.h"

MQTTSocket socket;
LedIndicator indicator;
Lock lock;
Logger logger;

void setup() {
  logger.begin();
  lock.begin();
  indicator.begin();

  socket.onWifiConnecting(logSSIDAndSignalStatusConnectingWifi)
      .onWifiConnected(logIPAndSignalStatusConnectedWifi)
      .onMQTTConnecting(logAndSignalStatusConnectingBroker)
      .onMQTTDisconnected(logAndSignalStatusDisconnectedBroker)
      .onMQTTConnected(logAndSignalStatusConnectedBroker)
      .onMessage(attendToRequest)
      .build();
}

void loop() { socket.loop(); }

void logSSIDAndSignalStatusConnectingWifi(const char *wifi_ssid) {
  logger.log(String("Connecting to wifi: ") + wifi_ssid);
  indicator.blink();
}

void logIPAndSignalStatusConnectedWifi(const char *local_ip) {
  logger.log(String("Connected to wifi with IP: ") + local_ip);
  indicator.off();
}

void logAndSignalStatusConnectingBroker() {
  logger.log("Connecting to MQTT Broker");
  indicator.blink();
}

void logAndSignalStatusDisconnectedBroker(int mqtt_error_code) {
  logger.log(String("Device disconnected with error code: ") +
             String(mqtt_error_code) + ". Reconnecting in 2seg...");
  indicator.on();
  delay(2000);
}

void logAndSignalStatusConnectedBroker(const char *broker_host,
                                       uint16_t broker_ip) {
  logger.log(String("Connected to MQTT Broker: ") + broker_host + ":" +
             String(broker_ip));
  indicator.off();
}

void attendToRequest(char *t, uint8_t *m, unsigned int l) {
  String topic = String(t);
  String message;
  for (int i = 0; i < l; i++) {
    message += (char)m[i];
  }

  logger.log(String("Message received: ") + topic + ": " + message);

  if (message == MQTT_MSG_TO_OPEN_LOCKER) {
    lock.open();
    logger.log("Locker opened");
  } else if (message == MQTT_MSG_TO_CLOSE_LOCKER) {
    lock.close();
    logger.log("Locker closed");
  }
}

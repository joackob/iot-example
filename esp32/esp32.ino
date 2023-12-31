/********
Rui Santos
Complete project details at https://randomnerdtutorials.com
*********/

// bibliotecas

// Archivos de programa
#include "./src/lock.h"
#include "./src/indicator.h"
#include "./src/logger.h"
#include "./src/mqtt.h"

// Settings
#include "wifi_config.h"
#include "mqtt_config.h"

// MQTT channel
MQTT mqtt;

// led
LedIndicator indicator;

// cerradura;
Lock lock;

// logger
Logger logger;

void onWifiConnecting()
{
  indicator.blink();
}

void onWifiConnected()
{
  indicator.off();
}

void onMQTTDisconnected()
{
  indicator.blink();
}

void onMQTTConnected()
{
  indicator.off();
}

void onMessage(String topic, String message)
{
  logger.logTopicAndMessage(topic, message);
  if (topic == MQTT_TOPIC)
  {
    if (message == MQTT_MSG_TO_OPEN_LOCKER)
    {
      lock.open();
    }
    else if (message == MQTT_MSG_TO_CLOSE_LOCKER)
    {
      lock.close();
    }
  }
}

void setup()
{
  logger.logSSIDWifiToConnect();
  mqtt.onWifiConnecting(onWifiConnecting)
      .onWifiConnected(onWifiConnected)
      .onMQTTDisconnected(onMQTTDisconnected)
      .onMQTTConnected(onMQTTConnected)
      .onMessage(onMessage)
      .build();
}

void loop()
{
  mqtt.loop();
}

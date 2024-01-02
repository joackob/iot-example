import fs from "fs";
import { print } from "./print.mjs";

const configMQTT = {
  "mqtt-host": "192.168.0.122",
  "mqtt-port": 1883,
  "mqtt-topic": "esp32/locker",
  "mqtt-msg-to-close": "close",
  "mqtt-msg-to-open": "open",
};

const configESP32 = () => {
  const mqttConfig = [
    "#ifndef MQTT_CONFIG_H",
    "#define MQTT_CONFIG_H",
    "",
    `#define MQTT_HOST "${configMQTT["mqtt-host"]}"`,
    `#define MQTT_PORT ${configMQTT["mqtt-port"]}`,
    `#define MQTT_TOPIC "${configMQTT["mqtt-topic"]}"`,
    `#define MQTT_MSG_TO_CLOSE_LOCKER "${configMQTT["mqtt-msg-to-close"]}"`,
    `#define MQTT_MSG_TO_OPEN_LOCKER "${configMQTT["mqtt-msg-to-open"]}"`,
    "",
    `#endif //!MQTT_CONFIG_H`,
  ];
  fs.writeFileSync("./esp32/mqtt_config.h", mqttConfig.join("\n"));
};

const configAppToDev = () => {
  const mqttConfig = [
    'NODE_ENV="development"',
    `MQTT_HOST="mqtt://${configMQTT["mqtt-host"]}:${configMQTT["mqtt-port"]}"`,
    `MQTT_TOPIC="${configMQTT["mqtt-topic"]}"`,
    `MQTT_MSG_TO_CLOSE_LOCKER="${configMQTT["mqtt-msg-to-close"]}"`,
    `MQTT_MSG_TO_OPEN_LOCKER="${configMQTT["mqtt-msg-to-open"]}"`,
  ];

  fs.writeFileSync("./app/.env", mqttConfig.join("\n"));
};

print("Export config to ESP32 and APP");
configESP32();
configAppToDev();

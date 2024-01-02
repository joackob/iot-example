import { print } from "./print.mjs";
import { exec } from "./exec.mjs";

print("install deps of app");
exec("cd app && npm install");

print("update board manager for esp32");
const urls = [
  "https://arduino.esp8266.com/stable/package_esp8266com_index.json",
  "https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json",
  "https://dl.espressif.com/dl/package_esp32_index.json",
];
urls.forEach((url) => {
  exec(`arduino-cli config add board_manager.additional_urls ${url}`);
});
exec("arduino-cli core update-index");
exec("arduino-cli core install esp32:esp32");

print("install deps of esp32");
const libs = ["WiFi", "PubSubClient", "ESP32Servo"];
libs.forEach((lib) => {
  exec(`arduino-cli lib install ${lib}`);
});

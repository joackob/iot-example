import { execSync } from "child_process";

const exec = (command) => {
  execSync(command, { stdio: "inherit" });
};

const print = (message) => {
  console.info("----------------------------------------");
  console.info(message);
  console.info("----------------------------------------");
};

// install deps of app
print("install deps of app");
exec("cd app && npm install");

// install deps of esp32
print("update board manager for esp32");
const urls = [
  "https://arduino.esp8266.com/stable/package_esp8266com_index.json",
  "https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json",
  "https://dl.espressif.com/dl/package_esp32_index.json",
];
urls.forEach((url) => {
  exec(`arduino-cli config add board_manager.additional-urls ${url}`);
});
exec("arduino-cli core update-index");
exec("arduino-cli core install esp32:esp32");

print("install deps of esp32");
const libs = ["WiFi", "PubSubClient", "ESP32Servo"];
libs.forEach((lib) => {
  exec(`arduino-cli lib install ${lib}`);
});

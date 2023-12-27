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
print("install deps of esp32");
const libs = ["WiFi", "PubSubClient", "ESP32Servo"];
libs.forEach((lib) => {
  exec(`arduino-cli lib install ${lib}`);
});

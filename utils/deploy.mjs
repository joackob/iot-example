import { execSync } from "child_process";

const exec = (command) => {
  execSync(command, { stdio: "inherit" });
};

const print = (message) => {
  console.info("----------------------------------------");
  console.info(message);
  console.info("----------------------------------------");
};

print("upload code to esp32");
exec("cd esp32 && arduino-cli upload");

print("build app");
exec("cd app && npm run start");

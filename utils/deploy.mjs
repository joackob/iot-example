import { print } from "./print.mjs";
import { exec } from "./exec.mjs";

print("upload code to esp32");
exec("cd esp32 && arduino-cli upload");

print("build app");
exec("cd app && npm run start");

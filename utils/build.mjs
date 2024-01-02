import { print } from "./print.mjs";
import { exec } from "./exec.mjs";

print("build app");
exec("cd app && npm run build");

print("compile code to esp32");
exec("cd esp32 && arduino-cli compile");

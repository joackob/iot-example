import { print } from "./print.mjs";
import { exec } from "./exec.mjs";

exec("node ./utils/config.mjs");

print("Build app");
exec("cd app && npm run build");

print("Compile code to esp32");
exec("cd esp32 && arduino-cli compile");

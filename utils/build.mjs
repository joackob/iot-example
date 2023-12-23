const exec = (command) => {
  execSync(command, { stdio: "inherit" });
};

const print = (message) => {
  console.info("----------------------------------------");
  console.info(message);
  console.info("----------------------------------------");
};

print("build app");
exec("cd app && npm run build");

print("compile and upload code to esp32");
exec("cd esp32 && arduino-cli compile");

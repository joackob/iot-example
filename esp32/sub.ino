/*********
Rui Santos
Complete project details at https://randomnerdtutorials.com
*********/
//bibliotecas
#include <WiFi.h>
#include <PubSubClient.h>//by Nick O'Leary
#include <ESP32Servo.h>//by Kevin Harrington,john k. Bennett

//Averiguar si estamos en modo AP o STA
// Reemplace las siguientes variables con su combinación SSID/Contraseña
const char* ssid = "ETEC-UBA";
//"Carlos";
//"ETEC-UBA";
const char* password = "ETEC-alumnos@UBA";
//"arduino95";
//"ETEC-alumnos@UBA";

// Add your MQTT Broker IP address, example:
//Agregue su dirección IP de MQTT Broker(ip donde esta el mosquito), ejemplo:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "192.168.0.184";
//"192.168.224.128"; yo
//"192.168.0.138"; equipo
//192.168.0.184 liz

WiFiClient espClient;                //para controlar la conexión de WiFi
PubSubClient mqttClient(espClient);  //para controlar la conexión de MQTT
long lastMsg = 0;                    //como si fuese un int
char msg[50];                        //cpomo si fuese un String
int value = 0;

// LED Pin
const int ledPin = 2;

Servo barrera;

void setup() {
  Serial.begin(115200);
  barrera.attach(23);

  setup_wifi();
  mqttClient.setServer(mqtt_server, 1883);  //puerto (1883)
  mqttClient.setCallback(callback);         //le digo a qué función del código debe llamar, cuando el servidor nos envía un mensaje

  pinMode(ledPin, OUTPUT);
}

void setup_wifi() {  //muesta lo que pasa en el monitor serie
  delay(10);
  // empezamos conectandolo a una red wifi
  Serial.println();
  Serial.print("Connecting to ");  //se esta conectando a cliente y el servidor
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  //trabaja en STA mandando un "." cada a la vez que se conecta
  }
  //se conecto
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String Led;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    Led += (char)message[i];
  }
  Serial.println();

  // Siéntase libre de agregar más declaraciones if para controlar más GPIOs con MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Si se recibe un mensaje sobre el tema esp32/output, verifica si el mensaje está "activado" o "desactivado".

  // Changes the output state according to the message
  //Cambia el estado de salida según el mensaje.
  if (String(topic) == "Carlosyliz") {
    Serial.print("Cambiar la salida a");
    if (Led == "on") {
      Serial.println("LedEncendido");
      digitalWrite(ledPin, HIGH);
      subirBarrera();
    } else if (Led == "off") {
      Serial.println("LedApagado");
      digitalWrite(ledPin, LOW);
      bajarBarrera();
    }
  }
}
void bajarBarrera() {
  barrera.write(0);
}
void subirBarrera() {
  barrera.write(90);
}

void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // Intenta conectar
    if (mqttClient.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      mqttClient.subscribe("#");
    } else {
      Serial.print("failed, codigo de error=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
  /*
long now = millis();
if (now - lastMsg > 5000) {
lastMsg = now;
// Temperature in Celsius
temperature = bme.readTemperature();
// Uncomment the next line to set temperature in Fahrenheit
// (and comment the previous temperature line)
//temperature = 1.8 * bme.readTemperature() + 32; // Temperature in Fahrenheit
// Convert the value to a char array
char tempString[8];
dtostrf(temperature, 1, 2, tempString);
Serial.print("Temperature: ");
Serial.println(tempString);
mqttClient.publish("esp32/temperature", tempString);




humidity = bme.readHumidity();
// Convert the value to a char array
char humString[8];
dtostrf(humidity, 1, 2, humString);
Serial.print("Humidity: ");
Serial.println(humString);
mqttClient.publish("esp32/humidity", humString);
}*/
}

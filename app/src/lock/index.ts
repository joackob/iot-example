import mqtt from "mqtt";

class LockSocket {
  socket: mqtt.MqttClient = mqtt.connect(process.env.MQTT_HOST || "");
  connected: boolean = false;
  orderToOpen: string = process.env.MQTT_MSG_TO_OPEN_LOCKER || "";
  orderToClose: string = process.env.MQTT_MSG_TO_CLOSE_LOCKER || "";

  constructor() {
    this.socket.on("connect", () => {
      this.socket.subscribe(process.env.MQTT_TOPIC || "", (error) => {
        this.connected = !error;
        console.log(error ? error : "Success at connect mqtt broker");
      });
    });
  }

  publish(message: string): void {
    if (!this.connected) return;
    this.socket.publish(process.env.MQTT_TOPIC || "", message);
  }

  sendOpenLocker(): void {
    this.publish(this.orderToOpen);
  }

  sendCloseLocker(): void {
    this.publish(this.orderToClose);
  }

  sendOrder(order: string): void {
    switch (order) {
      case this.orderToOpen: {
        this.sendOpenLocker();
        break;
      }
      case this.orderToClose: {
        this.sendCloseLocker();
        break;
      }
      default: {
        console.log("Order not found");
      }
    }
  }
}

export const lockSocket = new LockSocket();
export default LockSocket;

import { NextApiRequest, NextApiResponse } from "next";
import mqtt from "mqtt";

export default async function handler(
  req: NextApiRequest,
  res: NextApiResponse,
) {
  const { controller } = req.query;
  const client = mqtt.connect(process.env.MQTT_HOST || "");

  client.on("connect", () => {
    console.log("se conecto correctamente al server-mqtt");
    client.subscribe(process.env.MQTT_TOPIC || "", (err) => {
      if (!err) {
        if (controller === process.env.MQTT_CONTROLLER_TO_OPEN_LOCKER) {
          client.publish(
            process.env.MQTT_TOPIC || "",
            process.env.MQTT_MSG_TO_OPEN_LOCKER || "",
          );
        }

        if (controller === process.env.MQTT_CONTROLLER_TO_CLOSE_LOCKER) {
          client.publish(
            process.env.MQTT_TOPIC || "",
            process.env.MQTT_MSG_TO_CLOSE_LOCKER || "",
          );
        }
      }
    });
  });

  res.status(200).json({ ping: "pong" });
}

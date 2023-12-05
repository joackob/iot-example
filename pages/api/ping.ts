import { NextApiRequest, NextApiResponse } from "next";
import mqtt from "mqtt/*";
import {config} from "../../config"

export default async function handler(
    req: NextApiRequest,
    res: NextApiResponse
) {
    const client = mqtt.connect("mqtt://test.mosquitto.org");

    client.on("connect", () => {
        client.subscribe("presence", (err) => {
            if (!err) {
                client.publish("presence", "Hello mqtt");
            }
        });
    });

    client.on("message", (topic, message) => {
        // message is Buffer
        console.log(message.toString());
        client.end();
    });
    res.status(200).json({ ping: "pong" });
}
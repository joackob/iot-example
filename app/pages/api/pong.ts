import { NextApiRequest, NextApiResponse } from "next";
import mqtt from "mqtt";
import {config} from "../../config"

export default async function handler(
    req: NextApiRequest,
    res: NextApiResponse
) {
    // const client = mqtt.connect("http://192.168.0.184");
    const client = mqtt.connect("mqtt://10.9.120.141");

    client.on("connect", () => {
        console.log("se conecto");
        client.subscribe("Carlosyliz", (err) => {
            if (!err) {
                client.publish("Carlosyliz", "off");
            }
        });
    });

    // client.on("message", (topic, message) => {
    //     // message is Buffer
    //     console.log(message.toString());
    //     client.end();
    // });
    res.status(200).json({ ping: "pong" });
}
import { NextApiRequest, NextApiResponse } from "next";
import { lockSocket } from "../../../src/lock";

export default async function handler(
  req: NextApiRequest,
  res: NextApiResponse,
) {
  const { controller } = req.query;
  lockSocket.sendOrder(controller as string);
  res.status(200).json({ msg_send: controller });
}

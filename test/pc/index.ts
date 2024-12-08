/** @format */

import dgram from "dgram";
const socket = dgram.createSocket("udp4");

socket.bind(4210);

socket.connect(4210, "192.168.4.1", async () => {
    socket.on("message", (d: string) => {
			var data = d.toString();
			var paddle1Y = data.split(",")[0]
			var ballX = data.split(",")[1]
			var ballY = data.split(",")[2]
			socket.send(paddle1Y);
		});
});

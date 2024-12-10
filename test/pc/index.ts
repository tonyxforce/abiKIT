/** @format */

import dgram from "dgram";
const socket = dgram.createSocket("udp4");

socket.bind(4210);

socket.connect(4210, "192.168.4.1", async () => {
	socket.send("0");
    socket.on("message", (d: string) => {
			var data = d.toString();
			var paddle1Y = Number(data.split(",")[0])
			var ballX = Number(data.split(",")[1])
			var ballY = Number(data.split(",")[2])
			socket.send((48-paddle1Y).toString());
		});
		socket.on("close", ()=>{
			process.exit();
		})
});

/** @format */

var serialport = require("serialport");
var SerialPort = serialport.SerialPort;

var sp = new SerialPort({ path: "COM8", baudRate: 115200 });

const sleep = (ms) => new Promise((r) => setTimeout(r, ms));

sp.on("open", async () => {
    console.log("OPEN");
		sp.write("60")
		clickBtn(5);
		process.exit();
	});


async function clickBtn(num) {
    sp.write(`${num}1`);
    await sleep(100);
    sp.write(`${num}0`);
    await sleep(100);
}

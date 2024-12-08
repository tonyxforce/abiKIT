import {WebSocketServer, WebSocket} from "ws"

const defaultGameState = {
	paddle1Y: 0,
	paddle2Y: 0,
	ballX: 0,
	ballY: 0,
  ballSpeedX: 2,
  ballSpeedY: 2,
  score1: 0,
  score2: 0,
}

var gameState = defaultGameState;

const wss = new WebSocketServer({port: 8080});
wss.on("connection", (ws)=>{
ws.on("data", (data)=>{
	console.log(data.toString());
})
});
/** @format */

const FIRSTCHAR_GAME = 0;
const FIRSTCHAR_MENU = 1;
const FIRSTCHAR_SELECTED = 2;
const SerialFirstChar = [FIRSTCHAR_GAME, FIRSTCHAR_MENU, FIRSTCHAR_SELECTED];
const MENU_GAMES = 0;
const MENU_SETTINGS = 1;
const Menu = [MENU_GAMES, MENU_SETTINGS];
const GAME_MENU = 0;
const GAME_PONG = 1;
const GAME_SNAKE = 2;
const GAME_FLAPPYBIRD = 3;
const GAME_BREAKOUT = 4;
const GAME_DEFAULT = 5;
const GAME_TEST = 6;
const Game = [
    GAME_MENU,
    GAME_PONG,
    GAME_SNAKE,
    GAME_FLAPPYBIRD,
    GAME_BREAKOUT,
    GAME_DEFAULT,
    GAME_TEST,
];

var serialport = require("serialport");
var SerialPort = serialport.SerialPort;

var sp = new SerialPort({ path: "COM10", baudRate: 921600 });

const sleep = (ms) => new Promise((r) => setTimeout(r, ms));

sp.on("open", async () => {
    console.log("OPEN");

    //switchSelectedTo("02");
		//switchToMenu(MENU_SETTINGS);
		switchGameTo(GAME_PONG);

    process.exit();
});

function switchToMenu(newMenu) {
    if (!Menu.includes(newMenu)) return;
    sp.write(`${FIRSTCHAR_MENU}${newMenu}`);
}

function switchGameTo(newGame) {
    if (!Game.includes(newGame)) return;
    sp.write(`${FIRSTCHAR_GAME}${newGame}`);
}

function switchSelectedTo(newSelected) {
    sp.write(`${FIRSTCHAR_SELECTED}${newSelected}`);
}

// Define your settings here:
var serverSettings = {
	httpPort: 3000,
	serialPort: '/dev/cu.usbmodem1411',
	baudRate: 9600,
	logInConsole: true
};

// Setting up the HTTP server:
var app = require('express')();
var http = require('http').Server(app);
app.get('/', function(req, res) {
	res.sendFile(__dirname + '/browser/index.html');
});
app.get('/jquery', function(req, res) {
	res.sendFile(__dirname + '/browser/js/jquery-2.1.3.min.js');
});
app.get('/script', function(req, res) {
	res.sendFile(__dirname + '/browser/js/index.js');
});
app.get('/stylesheet', function(req, res) {
	res.sendFile(__dirname + '/browser/css/index.css');
});
http.listen(serverSettings.httpPort, function() {
	if (serverSettings.logInConsole === true) console.log('HTTP Server listening on port', serverSettings.httpPort);
});

// Setting up the WebSocket server (we use "ws" instead of "socket.io" in order to ensure the compatibility with Processing):
var WebSocketServer = require('ws').Server;
var wss = new WebSocketServer({
	server: http
});
wss.on('connection', function(ws) {
	if (serverSettings.logInConsole === true) console.log('WebSocket connected');
	ws.on('close', function() {
		if (serverSettings.logInConsole === true) console.log('WebSocket disconnected');
	});
});

// Setting up the Serial connection:
var serialport = require('serialport');
var SerialPort = serialport.SerialPort;
var serialPort = new SerialPort(serverSettings.serialPort, {
	baudrate: serverSettings.baudRate,
	parser: serialport.parsers.readline('\n')
});
serialPort.on('open', function () {
	if (serverSettings.logInConsole === true) console.log('Serial port open');
	serialPort.on('data', function(jsonData) {
		if (serverSettings.logInConsole === true) console.log('Serial data received:', jsonData);
		try {
			var objectData = JSON.parse(jsonData); // Just ensure that received data are valid
			try {
				wss.clients.forEach(function (client) { // Then broadcast them to all connected clients
					client.send(jsonData);
				});
			} catch (e) {
				if (serverSettings.logInConsole === true) console.log('Error while transmitting serial data:', e);
			}
		} catch (e) {
			if (serverSettings.logInConsole === true) console.log('Error while processing serial data:', e);
		}
	});
});
serialPort.on('close', function() {
	if (serverSettings.logInConsole === true) console.log('Serial port closed');
});
serialPort.on('error', function(e) {
	if (serverSettings.logInConsole === true) console.log('Serial port error:', e);
});

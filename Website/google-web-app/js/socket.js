class Socket {
	constructor() {
		this.socketId = -1;
		this.connected = false;
		this.init();
	}

	init() {
		chrome.sockets.tcp.create({}, function (createInfo) {
			this.socketId = createInfo.socketId
		});
	}

	send(mess) {
		log(">> " + mess)
		chrome.sockets.tcp.send(this.socketId, this.stringToArrayBuffer(mess), function (res) {
			console.log(res)
		})

	}

	onConnected() {
		log("Connected as " + this.socketId)
	}

	stringToArrayBuffer(string) {
		var arrayBuffer = new ArrayBuffer(string.length * 2);
		var buffer = new Uint8Array(arrayBuffer);
		for (var i = 0, stringLength = string.length; i < stringLength; i++) {
			buffer[i] = string.charCodeAt(i);
			// Was: buffer = string.charCodeAt(i);
		}
		return buffer;
	}

	connect(ip = "163.172.191.206", port = 8080) {
		chrome.sockets.tcp.connect(this.socketId, ip, port, this.onConnected)
	}
}

function log(text) {
	document.getElementById("log").value += text + "\r\n";
}

document.addEventListener("DOMContentLoaded", function() {
	log("Connecting ...")

	var socket = new Socket();
	socket.connect();
	socket.send("test")
});
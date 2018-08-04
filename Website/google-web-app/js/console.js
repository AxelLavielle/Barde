const DEFAULT_IP = "163.172.191.206"
const DEFAULT_PORT = 8080

function BardeLog(text) {
	document.getElementById("log").innerHTML += '<span>' + text + '</span></br>'
}

class Barde {

	constructor(){

		this.ip = DEFAULT_IP
		this.port = DEFAULT_PORT;
		this.connected = false;
		this.socket = new TcpClient(DEFAULT_IP, DEFAULT_PORT);
		this.feed = null;
		this.socket.addResponseListener(function (res){
			BardeLog("Server : " + res)
			console.log(res);
			BardeLog("To bas64")
		});
	}

	init() {
		BardeLog("initializing...");
		document.getElementById('ip').value = this.ip;
		document.getElementById('port').value = this.port;
		BardeLog("initializing OK");
	}

	onConnect(connect){
		BardeLog("Connected");
		document.getElementById('connect').style.display = 'none'
		document.getElementById('disconnect').style.display = 'block'
		document.getElementById('control-button-play').disabled = false;
		document.getElementById('control-button-pause').disabled = true;
		this.connected = true;
	}

	onDisconnect(){
		BardeLog("Disconnecting ...")
		document.getElementById('connect').style.display = 'block'
		document.getElementById('disconnect').style.display = 'none'
		document.getElementById('control-button-play').disabled = true;

		this.connected = false

	}

	connect() {
		this.socket.connect(this.onConnect)
	}

	send(data){
		this.socket.sendMessage(data);

	}

	play(){
		var buffer = new Uint8Array([0x2, 0, 0, 0, 0x12, 0, 0, 0, 0x0D, 0, 0, 0, 0x0A, 0, 0, 0]);
		this.send(buffer.buffer);
		document.getElementById('control-button-play').disabled = true;
		document.getElementById('control-button-pause').disabled = false;

		this.socket.addResponseListener(function (res){
			this.feed = res;
			BardeLog("Midi " + res);
		});

	}

	pause(){
		var buffer = new Uint8Array([0x2, 0, 0, 0, 0x32, 0, 0, 0, 0x0D, 0, 0, 0, 0x0A, 0, 0, 0]);
		this.send(buffer.buffer);
		document.getElementById('control-button-play').disabled = false;
		document.getElementById('control-button-pause').disabled = true;
	}

	disconnect(){
		this.socket.disconnect();
	}

}


document.addEventListener("DOMContentLoaded", function() {

	var BardePlayer = new Barde();

	BardePlayer.init();

	window.onload = function() {
		document.getElementById('connect').onclick = function fun(elem) {
			BardePlayer.connect();
		}
		document.getElementById('disconnect').onclick = function fun(elem) {
			BardePlayer.disconnect();
		}

		document.getElementById('control-button-play').onclick = function fun(elem) {
			BardePlayer.play();
		}


		document.getElementById('control-button-pause').onclick = function fun(elem) {
			BardePlayer.pause();
		}



	}
	document.addEventListener('DOMContentLoaded', function() {
		var elems = document.querySelectorAll('select');
		var instances = M.FormSelect.init(elems, options);
	});



});


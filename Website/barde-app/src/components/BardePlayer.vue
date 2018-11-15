<template>
  <div class="player">
    <barde-settings ref="settings"></barde-settings>
    <barde-console ref="console"></barde-console>
      <div class="player-controls">
        <div class="col s4">
          <div class="volume">
            <div class="row">
              <div class="col s10">
                  <p class="range-field">
                    <button   @click="playing ? CommandPause() : CommandPlay()" class="btn-floating waves-effect waves-light pink"><i class="material-icons">{{ playing ? 'pause' : 'play_arrow' }}</i></button>
                    <a @click="toggleMute()" class="btn-floating waves-effect waves-light pink"><i class="material-icons">volume_up</i></a>
                  </p>
              </div>
            </div>
          </div>
        </div>
        <div class="col s6">
          <p>
            <a class="btn-flat disabled">
              <span v-if="!playing">{{status}}</span>

            </a>
          </p>
        </div>
    </div>
  </div>
</template>

<script>

  import VueHowler from 'vue-howler'
  import MidiPlayer from 'midi-player-js'
  import BardeConsole from "@/components/player/BardeConsole"
  import BardeSettings from "@/components/player/BardeSettings"
  import HolwerPlayer from "@/components/HowlerPlayer"

  const CMD_PLAYER_PLAY     = [0x2, 0, 0, 0, 0x12, 0, 0, 0, 0x0D, 0, 0, 0, 0x0A, 0, 0, 0];
  const CMD_PLAYER_PAUSE    = [0x2, 0, 0, 0, 0x22, 0, 0, 0, 0x0D, 0, 0, 0, 0x0A, 0, 0, 0]

  const CMD_MUSICPARAM_STYLE_BLUES = [0x1, 0, 0, 0, 0x11, 0, 0, 0, 0x111, 0, 0, 0, 0x0D, 0, 0, 0, 0x0A, 0, 0, 0]
  const CMD_MUSICPARAM_ADDCHORD_PIANO = [0x1, 0, 0, 0, 0x11, 0, 0, 0, 0x1, 0, 0, 0, 0x0D, 0, 0, 0, 0x0A, 0, 0, 0]
  const CMD_MUSICPARAM_ADDCHORD_SAXO = [0x1, 0, 0, 0, 0x11, 0, 0, 0, 0x41, 0, 0, 0, 0x0D, 0, 0, 0, 0x0A, 0, 0, 0]

  const CMD_PLAYER_PLAY_RESPONSE = "OK : playing.";

  export default {
    components:{
      BardeConsole,
      BardeSettings,
      HolwerPlayer
    },
    data () {
      return {
        websocket : null,
        playing: false,
        status: "",
        file: null,
        player: null,
        lastResponse: null,
        responses: [CMD_PLAYER_PLAY_RESPONSE],
        actions: [this.onPlayResponse],
        data: []
      }
    },
    beforeMount(){
      this.getUser();
    },
    mounted () {
      this.initWebSocket(process.env.NODE_ENV === 'development' ? "ws://163.172.191.206:23344" : "ws://163.172.191.206:23345");
    },
    methods: {
      initWebSocket(wsUri){
        this.websocket = new WebSocket(wsUri, ['binary', 'base64', 'arrayBuffer']);
        this.websocket.onopen = this.onConnect;
        this.websocket.onclose = this.onDisconnect;
        this.websocket.onmessage = this.onMessage;
        this.websocket.onerror = this.onError;

        },
      initPlayer(){

        this.player = new MidiPlayer.Player();
        this.player.on('fileLoaded', function() {
          console.log("file loaded")
        });
        this.player.on('playing', function(currentTick) {
        });
        this.player.on('midiEvent', function(event) {
          // Do something when a MIDI event is fired.
          // (this is the same as passing a function to MidiPlayer.Player() when instantiating.
        });
        this.player.on('endOfFile', function() {
          console.log("endOfFile")
        });

      },
      onConnect(){
        this.$refs.console.log("Barde is connected")
        this.status = "Connected";

      } ,
      blobToString(b) {
        var u, x;
        u = URL.createObjectURL(b);
        x = new XMLHttpRequest();
        x.open('GET', u, false); // although sync, you're not fetching over internet
         x.send();
        URL.revokeObjectURL(u);
        return x.responseText;
  },
      onMessage(e){
        //let message = this.arrayBufferToString(e.data);
      let message = this.blobToString(e.data);
        console.log(this.blobToString(e.data))

        if (message.includes("OK :")){
          this.$refs.console.log("SUCCESS" + message)
        }
        else if (message.includes("Bad Request")){
          this.$refs.console.log("WARNING " + message)

        }

        this.checkAction(e.data, message);
      },
      debutMessage(){


      },
      onDisconnect(){
        this.status = "Disconnected";

        this.$refs.console.log("disconnected.")

      },
      onError(e){
        console.log(e);
        this.$refs.console.log("Service not available")

      },
      commandToBuffer(cmd){
        var buffer = new Uint8Array(cmd);
        return buffer
      },
      onPlayResponse(){
        this.data = [];
        this.lastResponse = CMD_PLAYER_PLAY_RESPONSE;
      },
      arrayBufferToString(buffer) {
        return String.fromCharCode.apply(null, new Uint8Array(buffer));
      },
      base64ArrayBuffer(arrayBuffer) {
        var
          base64 = "",
          encodings = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
          bytes = new Uint8Array(arrayBuffer),
          byteLength = bytes.byteLength,
          byteRemainder = byteLength % 3,
          mainLength = byteLength - byteRemainder,
          a,
          b,
          c,
          d,
          chunk;

        for (var i = 0; i < mainLength; i = i + 3) {
          chunk = (bytes[i] << 16) | (bytes[i + 1] << 8) | bytes[i + 2];

          a = (chunk & 16515072) >> 18;
          c = (chunk & 4032) >> 6;
          d = chunk & 63;

          base64 += encodings[a] + encodings[b] + encodings[c] + encodings[d];
        }

        if (byteRemainder == 1) {
          chunk = bytes[mainLength];
          a = (chunk & 252) >> 2;
          b = (chunk & 3) << 4;
          base64 += encodings[a] + encodings[b] + "==";
        }
        else if (byteRemainder == 2) {
          chunk = (bytes[mainLength] << 8) | bytes[mainLength + 1];
          a = (chunk & 64512) >> 10;
          b = (chunk & 1008) >> 4;
          c = (chunk & 15) << 2;
          base64 += encodings[a] + encodings[b] + encodings[c] + "=";
    }
    return base64;
  },
      checkAction(buffer, message){
        var index = this.inResponseArray(String(message));

        if (index){
          this.data = [];
          this.actions[index - 1]();
        }
        else {
          this.data.push(buffer);
          if (this.data.length === 4 && this.lastResponse === CMD_PLAYER_PLAY_RESPONSE) {
            this.$refs.console.log("GENERATING MUSIC")
          }
        }

      },
      createFile(buffer){
        const blob = new Blob( [ buffer ], { type: 'audio/midi' } );

      },
      inResponseArray(response){
        return this.responses.includes(this.epurString(String(response)))
      },
      sendCommand(cmd, name){
        this.$refs.console.log(name, "me")
        this.websocket.send(this.commandToBuffer(cmd))
      },
      addSlashes(str){
        str = str.replace(/\\'/g, '\'');
        str = str.replace(/\\"/g, '"');
        str = str.replace(/\\0/g, '\0');
        str = str.replace(/\\\\/g, '\\');
        return str
        },
      CommandPlay(){
        this.playing = true;
        this.sendCommand(CMD_PLAYER_PLAY, "PLAY");
        },
      CommandPause(){
        this.$refs.console.log("PAUSE", "me")
        this.playing = false;
        this.sendCommand(CMD_PLAYER_PAUSE);

      },
      epurString(str){
        str = str.substr(12);
        str = str.substring(0, str.length - 2)
        return str
      },
      playFile(){

        this.player.loadArrayBuffer(this.file.buffer)
      },
      getUser(){
        var jwtDecode = require('jwt-decode');
        this.user = jwtDecode(this.$auth.token('default'));
      },
      add() {
        // Emit the server side
        this.$socket.emit("add", { a: 5, b: 3 });
      }
    },

  }
</script>


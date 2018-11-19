<template>
  <div class="player">
    <barde-settings :onStyleChange="onStyleChange" ref="settings"></barde-settings>
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
import VueHowler from "vue-howler";
import MidiPlayer from "midi-player-js";
import BardeConsole from "@/components/player/BardeConsole";
import BardeSettings from "@/components/player/BardeSettings";
import HolwerPlayer from "@/components/HowlerPlayer";
import blobToArrayBuffer from "blob-to-arraybuffer";
import FileSaver from "file-saver";

const CMD_PLAYER_PLAY = [
  0x2,
  0,
  0,
  0,
  0x12,
  0,
  0,
  0,
  0x0d,
  0,
  0,
  0,
  0x0a,
  0,
  0,
  0
];
const CMD_PLAYER_PAUSE = [
  0x2,
  0,
  0,
  0,
  0x22,
  0,
  0,
  0,
  0x0d,
  0,
  0,
  0,
  0x0a,
  0,
  0,
  0
];

const BACKSLASHR = [0x0d, 0, 0, 0];
const BACKSLASHN = [0x0a, 0, 0, 0];

const MUSIQUEPARAM = 0x1;
const STYLE = 0x11;
const JAZZ = 0x111;

const CMD_MUSICPARAM_STYLE_BLUES = [
  0x1,
  0,
  0,
  0,
  0x11,
  0,
  0,
  0,
  0x11,
  0x2,
  0,
  0,
  0x0d,
  0,
  0,
  0,
  0x0a,
  0,
  0,
  0
];
const CMD_MUSICPARAM_STYLE_RAGGEA = [
  0x1,
  0,
  0,
  0,
  0x11,
  0,
  0,
  0,
  0x11,
  0x1,
  0,
  0,
  0x0d,
  0,
  0,
  0,
  0x0a,
  0,
  0,
  0
];
const CMD_MUSICPARAM_ADDCHORD_PIANO = [
  0x1,
  0,
  0,
  0,
  0x11,
  0,
  0,
  0,
  0x111,
  0,
  0,
  0,
  0x0d,
  0,
  0,
  0,
  0x0a,
  0,
  0,
  0
];
const CMD_MUSICPARAM_ADDCHORD_SAXO = [
  0x1,
  0,
  0,
  0,
  0x11,
  0,
  0,
  0,
  0x41,
  0,
  0,
  0,
  0x0d,
  0,
  0,
  0,
  0x0a,
  0,
  0,
  0
];

const CMD_PLAYER_PLAY_RESPONSE = "OKplaying";

export default {
  components: {
    BardeConsole,
    BardeSettings,
    HolwerPlayer
  },
  data() {
    return {
      websocket: null,
      playing: false,
      status: "",
      file: null,
      player: null,
      lastResponse: null,
      responses: [CMD_PLAYER_PLAY_RESPONSE],
      actions: [this.onPlayResponse],
      data: []
    };
  },
  beforeMount() {
    this.getUser();
  },
  mounted() {
    this.initWebSocket(
      process.env.NODE_ENV === "development"
        ? "ws://163.172.191.206:23344"
        : "ws://163.172.191.206:23345"
    );
    this.initPlayer();
  },
  methods: {
    formatStyle(styleValue) {
      let style = [
        0x1,
        0,
        0,
        0,
        0x11,
        0,
        0,
        0,
        0x11,
        parseInt(styleValue),
        0,
        0,
        0x0d,
        0,
        0,
        0,
        0x0a,
        0,
        0,
        0
      ];
      return style;
    },
    onStyleChange(value) {
      let style = value.toString().split(":");
      this.sendCommand(this.formatStyle(style[0]), "USE " + style[1]);
    },
    initWebSocket(wsUri) {
      this.websocket = new WebSocket(wsUri, [
        "binary",
        "base64",
        "arrayBuffer"
      ]);
      this.websocket.onopen = this.onConnect;
      this.websocket.onclose = this.onDisconnect;
      this.websocket.onmessage = this.onMessage;
      this.websocket.onerror = this.onError;
    },
    initPlayer() {
      this.player = new MidiPlayer.Player();
      this.player.on("fileLoaded", function() {
        console.log("file loaded");
      });
      this.player.on("playing", function(currentTick) {});
      this.player.on("midiEvent", function(event) {
        // Do something when a MIDI event is fired.
        // (this is the same as passing a function to MidiPlayer.Player() when instantiating.
      });
      this.player.on("endOfFile", function() {
        console.log("endOfFile");
      });
    },
    onConnect() {
      this.$refs.console.log("Barde is connected");
      this.status = "Connected";
    },
    blobToArrayBuffer(blob) {
      var arrayBuffer;
      var fileReader = new FileReader();
      fileReader.onload = function(event) {
        arrayBuffer = event.target.result;
      };
      fileReader.readAsArrayBuffer(blob);
    },
    blobToString(b) {
      var u, x;
      u = URL.createObjectURL(b);
      x = new XMLHttpRequest();
      x.open("GET", u, false); // although sync, you're not fetching over internet
      x.send();
      URL.revokeObjectURL(u);
      return x.responseText;
    },
    async onMessage(e) {
      let arrayBuffer = await fetch(URL.createObjectURL(e.data)).then(res =>
        res.arrayBuffer()
      );
      arrayBuffer = arrayBuffer.slice(4);
      let message = this.blobToString(e.data).replace(/^[a-z\d\-_\s]+$/i, "");
      if (message !== "hello\r\n")
        this.$refs.console.log(
          message,
          "server",
          message.includes("OK :") ? "ok" : "ko"
        );

      if (this.isMidi(message)) {
        const player = new MidiPlayer.Player();
        player.loadArrayBuffer(arrayBuffer);
        player.play();
      }
      /*
      blobToArrayBuffer(e.data).then(buffer => {
          this.checkAction(buffer.srcElement.result, message, e);
        })
      //

     */
    },
    debutMessage() {},
    arrayContains(needle, arrhaystack) {
      console.log(
        needle.substr(3),
        "in ",
        arrhaystack,
        arrhaystack.indexOf(needle.substr(3))
      );
      return arrhaystack.indexOf(needle) > -1;
    },
    removeNonPrintableChar(str) {
      return str.replace(/[^ -~]+/g, "");
    },
    onDisconnect() {
      this.status = "Disconnected";

      this.$refs.console.log("disconnected.");
    },
    onError(e) {
      console.log(e);
      this.$refs.console.log("Service not available");
    },
    commandToBuffer(cmd) {
      var buffer = new Uint8Array(cmd);
      return buffer;
    },
    onPlayResponse() {
      console.log("play response");
      this.data = [];
      this.lastResponse = CMD_PLAYER_PLAY_RESPONSE;
    },
    arrayBufferToString(buffer) {
      return String.fromCharCode.apply(null, new Uint8Array(buffer));
    },
    base64ArrayBuffer(arrayBuffer) {
      var base64 = "",
        encodings =
          "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
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
      } else if (byteRemainder == 2) {
        chunk = (bytes[mainLength] << 8) | bytes[mainLength + 1];
        a = (chunk & 64512) >> 10;
        b = (chunk & 1008) >> 4;
        c = (chunk & 15) << 2;
        base64 += encodings[a] + encodings[b] + encodings[c] + "=";
      }
      return base64;
    },
    isMidi(str) {
      if (str.indexOf("MTh") !== -1) return true;
      return false;
    },

    createMidi(blob) {
      console.log(blob);
      // FileSaver.saveAs(blob, "./hello world.mid");
    },
    checkAction(buffer, message, blob) {
      if (message.indexOf("MTh") >= 0) {
        //this.createMidi(blob.data);
      }
      /*
        var index = this.strInArray(message, this.responses);
        console.log(message, " index: ", index)
        if (index !== -1){
          this.data = [];
          console.log("calling ", index)
          this.actions[index]();
        }
        else {
          this.data.push(buffer);
          //this.createFile(buffer)
       console.log(this.lastResponse, CMD_PLAYER_PLAY_RESPONSE, this.data.length === 4 && this.lastResponse === CMD_PLAYER_PLAY_RESPONSE)
          if (this.data.length === 4 && this.lastResponse === CMD_PLAYER_PLAY_RESPONSE) {
            this.$refs.console.log("GENERATING MUSIC")
          }
        }
        */
    },
    saveData(data, filename) {
      var a = document.createElement("a");
      document.body.appendChild(a);
      a.style = "display: none";
      return function(data, fileName) {
        var json = JSON.stringify(data),
          blob = new Blob([json], { type: "octet/stream" }),
          url = window.URL.createObjectURL(blob);
        a.href = url;
        a.download = fileName;
        a.click();
        window.URL.revokeObjectURL(url);
      };
    },
    createFile(buffer) {
      consike;
      /*
           BUFFER -> BARDE.MID / .MIDI
      */
    },
    strInArray(str, array) {
      for (var i = 0; i < array.length; i++) {
        if (array[i].indexOf(str) !== -1) {
          return i;
        }
      }
      return -1;
    },
    inResponseArray(response) {
      return this.responses.includes(response);
    },
    sendCommand(cmd, name) {
      this.$refs.console.log(name, "me");
      this.websocket.send(this.commandToBuffer(cmd));
    },
    addSlashes(str) {
      str = str.replace(/\\'/g, "'");
      str = str.replace(/\\"/g, '"');
      str = str.replace(/\\0/g, "\0");
      str = str.replace(/\\\\/g, "\\");
      return str;
    },
    CommandPlay() {
      this.playing = true;
      this.sendCommand(CMD_PLAYER_PLAY, "PLAY");
    },
    CommandPause() {
      this.$refs.console.log("PAUSE", "me");
      this.playing = false;
      this.sendCommand(CMD_PLAYER_PAUSE);
    },
    epurString(str) {
      str = str.substr(12);
      str = str.substring(0, str.length - 2);
      return str;
    },
    playFile() {
      this.player.loadArrayBuffer(this.file.buffer);
    },
    getUser() {
      var jwtDecode = require("jwt-decode");
      this.user = jwtDecode(this.$auth.token("default"));
    },
    add() {
      // Emit the server side
      this.$socket.emit("add", { a: 5, b: 3 });
    }
  }
};
</script>


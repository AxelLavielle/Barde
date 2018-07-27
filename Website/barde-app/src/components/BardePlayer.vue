<template>
  <div class="player">
    <div class="card-body">
      <div class="messages" v-for="(msg, index) in messages" :key="index">
        <p><span class="font-weight-bold">{{ msg }}</span></p>
      </div>
    </div>
      <div class="player-controls">
        <div class="col s4">
          <div class="volume">
            <div class="row">
              <div class="col s10">

                  <p class="range-field">
                    <button :disabled="!socket.connected" @click="playSocket()" class="btn-floating waves-effect waves-light pink"><i class="material-icons">{{ playing ? 'pause' : 'play_arrow' }}</i></button>

                    <a @click="toggleMute()" class="btn-floating waves-effect waves-light pink"><i class="material-icons">volume_up</i></a>
                  </p>



              </div>
            </div>
          </div>
        </div>
        <div class="col s6">
          <p>
            <a class="btn-flat disabled">
              <span v-if="playing">BARDE {{muted ? '- muted' : ''}}</span>
              <span v-if="!playing">{{socket.connected ? 'connected' : 'not connected ' }}</span>

            </a>
          </p>
        </div>
    </div>
  </div>
</template>

<script>

  import VueHowler from 'vue-howler'
  import io from 'socket.io-client';

  export default {
    mixins: [VueHowler, {

    }],
    data () {
      return {
        socket : io('163.172.128.43:8080'),
        isConnected: false,
        messages: [],
        user:{}


      }
    },
    beforeMount(){
      this.getUser();
    },
    mounted(){
      this.socket.on('connected', (data) => {
        console.log(data)
        this.messages = [...this.messages, data.message];
      });
      this.socket.on('message', (data) => {
        this.messages = [...this.messages, data.message];
      });
    },
    methods: {
      playSocket(){
        console.log("play")
        this.messages = [...this.messages, this.user.name.userName + ": P"];
        this.socket.emit('message', {
          message: "P"
        });

          this.messages = [...this.messages, "������MThd������������`MTrk����7��ￃ9��ￄ��ￅA￀��9��￁��ￂA��￉Z��ￊR��ￋTﾇgﾐ��d��d��d��ﾑ��d��d��d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ��d��d��d��ﾁ��d��d��d��ﾑ��d��d��d��ﾂ��d��d��d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ��d��d��d��ﾁ��d��d��d��ﾑ��d��d��d��ﾂ��d��d��d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ��d��d��d��ﾁ��d��d��d��ﾑ��d��d��d��ﾂ��d��d��d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ5d��Ed��0d��ﾁ��d��d��d��ﾑ5d��Ed��0d��ﾂ��d��d��d��ﾒ5d��Ed��0dﾇhﾓAd��ﾔAd��ﾕAdﾄXﾃAd��ﾄAd��ﾅAdﾒ`ﾀ5d��Ed��0d��ﾐ5d��Ed��0d��ﾁ5d��Ed��0d��ﾑ5d��Ed��0d��ﾂ5d��Ed��0d��ﾒ5d��Ed��0dﾇhﾓAd��ﾔAd��ﾕAdﾄXﾃAd��ﾄAd��ﾅAdﾒ`ﾀ5d��Ed��0d��ﾐ��d��d��d��ﾁ5d��Ed��0d��ﾑ��d��d��d��ﾂ5d��Ed��0d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ��d��d��d��ﾁ��d��d��d��ﾑ��d��d��d��ﾂ��d��d��d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ7d��Gd��2d��ﾁ��d��d��d��ﾑ7d��Gd��2d��ﾂ��d��d��d��ﾒ7d��Gd��2dﾇhﾓCd��ﾔCd��ﾕCdﾄXﾃCd��ﾄCd��ﾅCdﾒ`ﾀ7d��Gd��2d��ﾐ5d��Ed��0d��ﾁ7d��Gd��2d��ﾑ5d��Ed��0d��ﾂ7d��Gd��2d��ﾒ5d��Ed��0dﾇhﾓAd��ﾔAd��ﾕAdﾄXﾃAd��ﾄAd��ﾅAdﾒ`ﾀ5d��Ed��0d��ﾐ��d��d��d��ﾁ5d��Ed��0d��ﾑ��d��d��d��ﾂ5d��Ed��0d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ7d��Gd��2d��ﾁ��d��d��d��ﾑ7d��Gd��2d��ﾂ��d��d��d��ﾒ7d��Gd��2dﾇhﾓCd��ﾔCd��ﾕCdﾄXﾃCd��ﾄCd��ﾅCdﾊx/��ﾇhﾀ7d��Gd��2d��ﾁ7d��Gd��2d��ﾂ7d��Gd��2d"];


      },
      sendMessage(e) {
        e.preventDefault();

        this.$socket.emit('SEND_MESSAGE', {
          user: this.user,
          message: this.message
        });
        this.message = ''
      },
      getUser(){
        var jwtDecode = require('jwt-decode');
        this.user = jwtDecode(this.$auth.token('default'));
      },
      add() {
        // Emit the server side
        this.$socket.emit("add", { a: 5, b: 3 });
      },
      getMidi(){
        this.messages = [...this.messages, "������MThd������������`MTrk����7��ￃ9��ￄ��ￅA￀��9��￁��ￂA��￉Z��ￊR��ￋTﾇgﾐ��d��d��d��ﾑ��d��d��d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ��d��d��d��ﾁ��d��d��d��ﾑ��d��d��d��ﾂ��d��d��d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ��d��d��d��ﾁ��d��d��d��ﾑ��d��d��d��ﾂ��d��d��d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ��d��d��d��ﾁ��d��d��d��ﾑ��d��d��d��ﾂ��d��d��d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ5d��Ed��0d��ﾁ��d��d��d��ﾑ5d��Ed��0d��ﾂ��d��d��d��ﾒ5d��Ed��0dﾇhﾓAd��ﾔAd��ﾕAdﾄXﾃAd��ﾄAd��ﾅAdﾒ`ﾀ5d��Ed��0d��ﾐ5d��Ed��0d��ﾁ5d��Ed��0d��ﾑ5d��Ed��0d��ﾂ5d��Ed��0d��ﾒ5d��Ed��0dﾇhﾓAd��ﾔAd��ﾕAdﾄXﾃAd��ﾄAd��ﾅAdﾒ`ﾀ5d��Ed��0d��ﾐ��d��d��d��ﾁ5d��Ed��0d��ﾑ��d��d��d��ﾂ5d��Ed��0d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ��d��d��d��ﾁ��d��d��d��ﾑ��d��d��d��ﾂ��d��d��d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ7d��Gd��2d��ﾁ��d��d��d��ﾑ7d��Gd��2d��ﾂ��d��d��d��ﾒ7d��Gd��2dﾇhﾓCd��ﾔCd��ﾕCdﾄXﾃCd��ﾄCd��ﾅCdﾒ`ﾀ7d��Gd��2d��ﾐ5d��Ed��0d��ﾁ7d��Gd��2d��ﾑ5d��Ed��0d��ﾂ7d��Gd��2d��ﾒ5d��Ed��0dﾇhﾓAd��ﾔAd��ﾕAdﾄXﾃAd��ﾄAd��ﾅAdﾒ`ﾀ5d��Ed��0d��ﾐ��d��d��d��ﾁ5d��Ed��0d��ﾑ��d��d��d��ﾂ5d��Ed��0d��ﾒ��d��d��dﾇhﾓ<d��ﾔ<d��ﾕ<dﾄXﾃ<d��ﾄ<d��ﾅ<dﾒ`ﾀ��d��d��d��ﾐ7d��Gd��2d��ﾁ��d��d��d��ﾑ7d��Gd��2d��ﾂ��d��d��d��ﾒ7d��Gd��2dﾇhﾓCd��ﾔCd��ﾕCdﾄXﾃCd��ﾄCd��ﾅCdﾊx/��ﾇhﾀ7d��Gd��2d��ﾁ7d��Gd��2d��ﾂ7d��Gd��2d"];

      },
      get() {
        this.$socket.emit("get", { id: 12 }, (response) => {
        });
      }
    },

  }
</script>


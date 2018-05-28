<template>
  <div class="player">
      <div class="player-controls">
        <div class="col s4">
          <div class="volume">
            <div class="row">
              <div class="col s10">

                  <p class="range-field">
                    <button @click="togglePlayback" class="btn-floating waves-effect waves-light pink"><i class="material-icons">{{ playing ? 'pause' : 'play_arrow' }}</i></button>

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
              <span v-if="!playing">NOTHING IS PLAYING </span>

            </a>
          </p>
        </div>
    </div>
  </div>
</template>

<script>

  import VueHowler from 'vue-howler'

  export default {
    mixins: [VueHowler],
    methods: {
      mounted(){
        this.$on("loaderror", function(data){
          console.log("loaderror", data);
        });

        this.$on(event, function(event){
          console.log("event", event);
        });


      }
    }
  }
</script>


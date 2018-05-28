<template>
  <div class="player">
      <div class="player-controls">
        <div class="col s4">
          <div class="volume">
            <div class="row">
              <div class="col s10">
                  <p class="range-field">
                    <button @click="togglePlayback" class="btn-floating waves-effect waves-light pink"><i class="material-icons">{{ playing ? 'pause' : 'play_arrow' }}</i></button>

                    <!--
                    <a class="btn-floating waves-effect waves-light pink"><i class="material-icons">volume_up</i></a>
-->
                  </p>
              </div>
            </div>
          </div>
        </div>
        <div class="col s6">
          <p>
            <a class="btn-flat disabled">Nothing is playing.</a>
          </p>
        </div>
    </div>
  </div>
</template>

<script>

  import VueHowler from 'vue-howler'

  export default {
    mixins: [VueHowler]
  }
</script>


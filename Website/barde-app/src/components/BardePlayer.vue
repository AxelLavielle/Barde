<template>
  <div class="player">
      <div class="player-controls">
        <div class="col s4">
          <div class="volume">
            <div class="row">
              <div class="col s10">
                  <p class="range-field">
                    <a class="btn-floating waves-effect waves-light pink"><i class="material-icons">play_arrow</i></a>
                    <a class="btn-floating waves-effect waves-light pink"><i class="material-icons">volume_up</i></a>
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

  export default {
    name: 'BardePlayer',
    data () {
      return {}
    }
  }
</script>


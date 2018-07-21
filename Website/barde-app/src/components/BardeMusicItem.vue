<template>
  <div class="card">
    <div class="card-content white-text">
      <img :src="image" class="responsive-img" alt="">
    </div>
    <div class="card-action">
      <a v-show="isPlaying" v-on:click="togglePlay()" class="btn-floating waves-effect waves-light pink"><i class="material-icons">pause</i></a>
      <a v-show="!isPlaying" v-on:click="togglePlay()" class="btn-floating waves-effect waves-light pink"><i class="material-icons">play_arrow</i></a>
      <span class="card-title">{{title}}</span>
    </div>
  </div>
</template>

<script>

  export default {
    name: 'BardeMusicItem',
    props: ['title', 'image'],
    data () {
      return {
        thumbnail : "thumbnail",
        isPlaying: false
      }
    },
    methods: {
      togglePlay(){
        this.isPlaying = !this.isPlaying;

      }
    }
  }
</script>


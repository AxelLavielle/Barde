<template>
  <div class="card">
    <div class="card-content white-text">
      <img src="../../static/img/barde-logo.png" class="responsive-img" alt="">
    </div>
    <div class="card-action">
      <span class="card-title">{{title}}</span>
    </div>
  </div>
</template>

<script>

  export default {
    name: 'BardeMusicItem',
    data () {
      return {
        title : "Title to discover",
        thumbnail : "thumbnail"
      }
    }
  }
</script>


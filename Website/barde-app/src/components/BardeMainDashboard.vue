<template>
  <div class="barde-main-dashboard">
    <div class="container">
      <h5 class="left-align">Music to discover</h5>
      <div class="row">
        <div class="col s4">
         <barde-music-item></barde-music-item>
        </div>
      </div>
    </div>
  </div>
</template>

<script>

  import BardeMusicItem from "./BardeMusicItem.vue";

  export default {
    components: {BardeMusicItem},
    name: 'BardeMainDashboard',
    data () {
      return {}
    }
  }
</script>


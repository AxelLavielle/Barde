<template>
  <div class="barde-main-dashboard">
    <div class="container">

    </div>
  </div>
</template>

<script>

  import BardeImage from '../../static/img/barde-logo.png';
  import BardeMusicItem from "./BardeMusicItem.vue";

  export default {
    components: {BardeMusicItem},
    name: 'BardeMainDashboard',
    data () {
      return {
       "image": BardeImage
      }
    }
  }
</script>


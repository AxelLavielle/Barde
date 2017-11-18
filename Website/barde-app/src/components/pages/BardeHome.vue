<template>
  <div class="barde">
    <div class="row">
      <div class="col l2 m3 s12 z-depth-2">
        <barde-profile-side-panel></barde-profile-side-panel>
      </div>
      <div class="col l10 m9 s12 barde-main">
        <barde-main-dashboard></barde-main-dashboard>
        <barde-player></barde-player>
      </div>
    </div>
  </div>
</template>

<script>
  import BardeProfileSidePanel from '@/components/BardeProfileSidePanel.vue'
  import BardeMainDashboard from '@/components/BardeMainDashboard.vue'
  import BardePlayer from '@/components/BardePlayer.vue'

  import '../../../static/css/player.css'


  export default {
    components: {
      BardeMainDashboard,
      BardePlayer,
      BardeProfileSidePanel
    },
    name: 'HelloWorld',
    data () {
      return {
        user : {}
      }
    },
    methods : {
      checkToken(){
          if (!this.$auth.token('default')){
            !this.$auth.logout();
          }
      },
      getUser(){
          var jwtDecode = require('jwt-decode');
          this.user = jwtDecode(this.$auth.token('default'));
          console.log(this.user)
      }
    },
    beforeMount(){
      this.getUser();
    }
  }
</script>


<template>
  <div class="barde">
    <div class="row">
      <div class="col l2 m3 s12 z-depth-2">
        <barde-profile-side-panel></barde-profile-side-panel>
      </div>
      <div class="col l10 m9 s12 barde-main">
        <barde-profile-edit></barde-profile-edit>
      </div>
    </div>
  </div>
</template>

<script>
  import BardeProfileSidePanel from '@/components/BardeProfileSidePanel.vue'
  import BardeProfileEdit from '@/components/BardeProfileEdit.vue'
  import BardePlayer from '@/components/BardePlayer.vue'
  import Materialize from 'materialize-css/dist/js/materialize.min.js'

  import '../../../static/css/player.css'

  export default {
    components: {
      BardeProfileEdit,
      BardeProfileSidePanel
    },
    name: 'HelloWorld',
    data () {
      return {
        user : {}
      }
    },
    mounted: function (){
      Materialize.updateTextFields()
    },
    methods : {
      checkToken(){
        if (!this.$auth.token('default')){
          !this.$auth.logout();
        }
      },
      getUser(){


      }
    },
    beforeMount(){

      //  this.getUser();
    },
    mounted(){

    }
  }
</script>


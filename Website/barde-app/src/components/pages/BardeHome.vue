<template>
  <div class="barde">


    <div class="row">
      <div class="col l2 m3 s12 z-depth-2">
        <barde-profile-side-panel></barde-profile-side-panel>
      </div>
      <div class="col l10 m9 s12 barde-main">
        <barde-player ref="player" :formats="this.formats" :sources="Player.feedUrl" html5 :loop="true" preload ></barde-player>
      </div>

      </div>
    </div>
</template>

<script>
  import BardeProfileSidePanel from '@/components/BardeProfileSidePanel.vue'
  import BardeMainDashboard from '@/components/BardeMainDashboard.vue'
  import BardePlayer from '@/components/BardePlayer.vue'


  import Preselections from '../../../static/data/preselections'
  import playerModel from '../models/playerModel'
  import instruments from '../../../src/assets/data/instruments'
  import '../../../static/css/player.css'


  export default {
    components: {
      BardeMainDashboard,
      BardePlayer,
      BardeProfileSidePanel
    },
    name: 'HelloWorld',
    props: ["status"],
    data () {
      return {
        preselectionsList : Preselections,
        formats: ['mp3'],
        instruments: instruments,
        Player : playerModel,
      }
    },
    methods : {
      checkToken(){
          if (!this.$auth.token('default')){
            this.$auth.logout();
          }
      },
      logout(){


        this.$auth.logout();
      },
      getUser(){
        this.checkToken();
          var jwtDecode = require('jwt-decode');
          this.user = jwtDecode(this.$auth.token('default'));
      },
      setIntrumentState(index, state){
        this.instruments[index].active = state;
      },
      setPreset(preset){
        this.Player = Preselections[0].data;

      },
      setInstruments(instruments){
        this.preselectionsList[data].data.instruments = instruments
      }
    },
    mounted(){


      var self = this;//vue
      $('select').material_select();
      $('#vueSelect').on('change', function () {
        self.$emit("change", this.value)
      });
      self.$on("change", function(data){
        this.setPreset(data);
      });

      self.$on("loaderror", function(data){
      });

      self.$on("playerror", function(data){
      });

      $('#selectStyle').on('change', function () {
        self.$emit("change", this.value)
      });
      self.$on("change", function(data){
        this.currentStyle = data
      });

    },
    beforeMount(){
      this.getUser();

    }
  }
</script>


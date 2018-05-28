<template>
  <div class="barde">
    <div class="row">
      <div class="col l2 m3 s12 z-depth-2">
        <barde-profile-side-panel></barde-profile-side-panel>
      </div>

      <div class="col l10 m9 s12 barde-main">
        <div class="barde-main-dashboard">
          <div class="container">
            <div class="">
              <div class="row">
                <div class="col s4">
                  <h4 class="left-align">Accords</h4>

                  <div class=" col s4 left-align">
                    <input disabled type="checkbox" id="Piano-accord" value="piano" v-model="Player.instruments.accords">
                    <label disabled for="Piano-accord">Piano</label>
                  </div>
                  <div class=" col s12 left-align">
                    <input disabled type="checkbox" id="trumpet-accord" value="trumpet-accord" v-model="Player.instruments.arpeges">
                    <label disabled for="trumpet-accord">trumpet</label>
                  </div>
                  <div class=" col s12 left-align">
                    <input disabled type="checkbox" id="saxophone-accord" value="saxophone-accord" v-model="Player.instruments.arpeges">
                    <label disabled for="saxophone-accord">saxophone</label>
                  </div>

                </div>

              <div class="col s4">
                <h4 class="left-align">Apreges</h4>

                <div class=" col s12 left-align">
                  <input disabled type="checkbox" id="piano-arpege" value="piano" v-model="Player.instruments.arpeges">
                  <label for="piano-arpege">Piano</label>
                </div>
                <div class=" col s12 left-align">
                  <input disabled type="checkbox" id="trumpet-arpege" value="trumpet" v-model="Player.instruments.arpeges">
                  <label for="trumpet-arpege">trumpet</label>
                </div>
                <div class=" col s12 left-align">
                  <input disabled type="checkbox" id="saxophone-arpege" value="saxophone" v-model="Player.instruments.arpeges">
                  <label for="saxophone-arpege">saxophone</label>
                </div>
              </div>

              <div class="col s4">
                <h4 class="left-align">Drums</h4>
                <div class="switch left-align">
                  <label>
                    Off
                    <input disabled v-model="Player.instruments.drums" type="checkbox">
                    <span class="lever"></span>
                    On
                  </label>
                </div>

              </div>


            </div>

            <div class="row">
              <div class="col s8 offset-s1">
                <input disabled v-model="Player.bpm" type="range" id="test5" min="60" max="150" />
              </div>
              <div class="col s2">
                <span>BPM : {{Player.bpm}}</span>
              </div>
            </div>
            </div>
          </div>
        </div>
        <barde-player :formats="this.formats" :sources="Player.feedUrl" html5 :loop="true" preload ></barde-player>
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
        console.log("changing");
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
        console.log("error", data);
      });

      self.$on("playerror", function(data){
        console.log("error", data);
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


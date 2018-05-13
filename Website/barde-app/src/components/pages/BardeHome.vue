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
              <div class="input-field col s12">
                <select id="vueSelect">
                  <option  :value="preselectionsList[0]" disabled selected>Choose a preselection</option>
                  <option v-for="(Preselection, index) in preselectionsList" :value="index">{{Preselection.name}}</option>
                </select>
              </div>

              or

              <div class="row">
                <div class="col s4">
                  <h4 class="left-align">Accords</h4>

                  <div class=" col s4 left-align">
                    <input type="checkbox" id="Piano-accord" value="piano" v-model="Player.instruments.accords">
                    <label for="Piano-accord">Piano</label>
                  </div>
                  <div class=" col s4 left-align">
                    <input type="checkbox" id="strings-accord" value="strings" v-model="Player.instruments.accords">
                    <label for="strings-accord">strings</label>
                  </div>

                </div>

              <div class="col s4">
                <h4 class="left-align">Apreges</h4>

                <div class=" col s4 left-align">
                  <input type="checkbox" id="piano-arpege" value="piano" v-model="Player.instruments.arpeges">
                  <label for="piano-arpege">Piano</label>
                </div>
                <div class=" col s4 left-align">
                  <input type="checkbox" id="strings-arpege" value="strings" v-model="Player.instruments.arpeges">
                  <label for="strings-arpege">strings</label>
                </div>
              </div>

              <div class="col s4">
                <h4 class="left-align">Drums</h4>
                <div class="switch left-align">
                  <label>
                    Off
                    <input v-model="Player.instruments.drums" type="checkbox">
                    <span class="lever"></span>
                    On
                  </label>
                </div>

              </div>


            </div>

            <div class="row">
              <div class="col s8 offset-s1">
                <input v-model="Player.bpm" type="range" id="test5" min="0" max="200" />
              </div>
              <div class="col s2">
                <span>BPM : {{Player.bpm}}</span>
              </div>
            </div>
            </div>
          </div>
        </div>
        <barde-player :sources="Player.feedUrl" html5 :loop="true" ></barde-player>
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
        formats: ['mp3', 'aac'],
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


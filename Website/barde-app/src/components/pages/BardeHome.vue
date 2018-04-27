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

              <div class="input-field col s12">
                <select id="">
                  <option  value="" disabled selected>Choose a style</option>
                  <option v-for="(style, index) in stylesList" :value="index">{{style}}</option>
                </select>
              </div>

              <div class="row">
                <div class="col s3" v-for="(intrument, index) in Player.instruments">
                  <input type="checkbox" :id="Player.instruments[index].name" v-model="Player.instruments[index].active">
                  <label :for="Player.instruments[index].name">{{Player.instruments[index].name }}</label>
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
        <barde-player :sources="Player.feedUrl" html5="true" :loop="true" ></barde-player>
      </div>
    </div>
  </div>
</template>

<script>
  import BardeProfileSidePanel from '@/components/BardeProfileSidePanel.vue'
  import BardeMainDashboard from '@/components/BardeMainDashboard.vue'
  import BardePlayer from '@/components/BardePlayer.vue'

  import Preselections from '../../../static/data/preselections'

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
        stylesList : [
          'Rap',
          'Raggea'
        ],
        formats: ['mp3', 'aac'],
        Player : {
          feedUrl : [
            "http://icecast.skyrock.net/s/natio_mp3_128k"
          ],
            instruments : [
            {
              'name' : 'piano',
              'active' : false
            },
            {
              'name' : 'drums',
              'active' : false
            }
          ],
          bpm : "120"
        }
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
        console.log(preset);
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


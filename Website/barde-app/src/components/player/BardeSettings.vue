<template>
    <div class="barde-main-dashboard">
      <div class="container">
        <div class="">
          <div class="row">
            <div class="col s12">
              <h4 class="left-align">Style</h4>
              <p>
              <label>
                <input class="with-gap" value="0x1:Blues" name="style"  v-model="style"  type="radio"  />
                <span>Blues</span>
              </label>
                <label>
                  <input class="with-gap" value="0x2:Raggea" name="style" v-model="style"  type="radio"  />
                  <span>Raggea</span>
                </label>
            </p>
            </div>
            <div class="col s4">
              <h4 class="left-align">Accords</h4>

              <div class=" col s4 left-align">
                <input  type="checkbox" id="Piano-accord" value="piano" v-model="Player.instruments.accords">
                <label  for="Piano-accord">Piano</label>
              </div>
              <div class=" col s12 left-align">
                <input  type="checkbox" id="trumpet-accord" value="trumpet-accord" v-model="Player.instruments.arpeges">
                <label  for="trumpet-accord">trumpet</label>
              </div>
              <div class=" col s12 left-align">
                <input  type="checkbox" id="saxophone-accord" value="saxophone-accord" v-model="Player.instruments.arpeges">
                <label  for="saxophone-accord">saxophone</label>
              </div>
            </div>

            <div class="col s4">
              <h4 class="left-align">Arpeges</h4>
              <div class=" col s12 left-align">
                <input  type="checkbox" id="piano-arpege" value="piano" v-model="Player.instruments.arpeges">
                <label for="piano-arpege">Piano</label>
              </div>
              <div class=" col s12 left-align">
                <input  type="checkbox" id="trumpet-arpege" value="trumpet" v-model="Player.instruments.arpeges">
                <label for="trumpet-arpege">trumpet</label>
              </div>
              <div class=" col s12 left-align">
                <input  type="checkbox" id="saxophone-arpege" value="saxophone" v-model="Player.instruments.arpeges">
                <label for="saxophone-arpege">saxophone</label>
              </div>
            </div>

            <div class="col s4">
              <h4 class="left-align">Drums</h4>
              <div class="switch left-align">
                <label>
                  Off
                  <input  v-model="drums" type="checkbox">
                  <span class="lever"></span>
                  On
                </label>
              </div>

            </div>


          </div>

          <div class="row">
            <div class="col s8 offset-s1">
              <input  v-model="bpm" type="range" id="test5" min="60" max="150" />
            </div>
            <div class="col s2">
              <span>BPM : {{bpm}}</span>
            </div>
          </div>
        </div>
      </div>
    </div>
</template>

<script>

  import instruments from '../../../src/assets/data/instruments'
  import playerModel from '../models/playerModel'


  export default {
    name: 'BardeSettings',
    props: ['onStyleChange', 'onDrumsChange', 'onBPMChange'],
    data () {
      return {
        instruments: instruments,
        Player : playerModel,
        style: null,
        drums: false,
        bpm: 120
      }
    },
    watch: {
      style: function (val) {
        this.onStyleChange(val);
      },
      drums: function (val) {
        this.onDrumsChange(val)
      },
      bpm: function (val){
        this.onBPMChange(val)
      }
    },
    methods : {
      styleChanged : this.onStyleChange
    }
  }
</script>

<style>
  [type="radio"]:not(:checked) + span, [type="radio"]:checked + span {
    position: relative;
    padding-left: 35px;
    cursor: pointer;
    display: inline-block;
    height: 25px;
    line-height: 25px;
    font-size: 1rem;
    -webkit-transition: .28s ease;
    transition: .28s ease;
    -webkit-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none
  }

  [type="radio"] + span:before, [type="radio"] + span:after {
    content: '';
    position: absolute;
    left: 0;
    top: 0;
    margin: 4px;
    width: 16px;
    height: 16px;
    z-index: 0;
    -webkit-transition: .28s ease;
    transition: .28s ease
  }

  [type="radio"]:not(:checked) + span:before, [type="radio"]:not(:checked) + span:after,
  [type="radio"]:checked + span:before, [type="radio"]:checked + span:after,
  [type="radio"].with-gap:checked + span:before, [type="radio"].with-gap:checked + span:after {
    border-radius: 50%
  }

  [type="radio"]:not(:checked) + span:before, [type="radio"]:not(:checked) + span:after {
    border: 2px solid #5a5a5a
  }

  [type="radio"]:not(:checked) + span:after {
    -webkit-transform: scale(0);
    transform: scale(0)
  }

  [type="radio"]:checked + span:before {
    border: 2px solid transparent
  }

  [type="radio"]:checked + span:after, [type="radio"].with-gap:checked + span:before,
  [type="radio"].with-gap:checked + span:after {
    border: 2px solid #26a69a
  }

  [type="radio"]:checked + span:after, [type="radio"].with-gap:checked + span:after {
    background-color: #26a69a
  }

  [type="radio"]:checked + span:after {
    -webkit-transform: scale(1.02);
    transform: scale(1.02)
  }

  [type="radio"].with-gap:checked + span:after {
    -webkit-transform: scale(0.5);
    transform: scale(0.5)
  }

  [type="radio"].tabbed:focus + span:before {
    -webkit-box-shadow: 0 0 0 10px rgba(0, 0, 0, 0.1);
    box-shadow: 0 0 0 10px rgba(0, 0, 0, 0.1)
  }

  [type="radio"].with-gap:disabled:checked + span:before {
    border: 2px solid rgba(0, 0, 0, 0.42)
  }

  [type="radio"].with-gap:disabled:checked + span:after {
    border: none;
    background-color: rgba(0, 0, 0, 0.42)
  }

  [type="radio"]:disabled:not(:checked) + span:before, [type="radio"]:disabled:checked + span:before {
    background-color: transparent;
    border-color: rgba(0, 0, 0, 0.42)
  }

  [type="radio"]:disabled + span {
    color: rgba(0, 0, 0, 0.42)
  }

  [type="radio"]:disabled:not(:checked) + span:before {
    border-color: rgba(0, 0, 0, 0.42)
  }

  [type="radio"]:disabled:checked + span:after {
    background-color: rgba(0, 0, 0, 0.42);
    border-color: #949494
  }
</style>

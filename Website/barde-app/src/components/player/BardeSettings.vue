<template>
  <div class="barde-main-dashboard">
    <div class="container">
      <div class>
        <div class="row">
          <div class="col s12">
            <h4 class="left-align">Style</h4>
            <div class="col s4 left-align">
              <label>
                <input class="with-gap" value="0x1:Blues" name="style" v-model="style" type="radio">
                <span>Blues</span>
              </label>
              <label>
                <input
                  class="with-gap"
                  value="0x2:Raggea"
                  name="style"
                  v-model="style"
                  type="radio"
                >
                <span>Raggea</span>
              </label>
            </div>
          </div>
          <div v-if="style" class="col s4">
            <h4 class="left-align">Chords</h4>

            <div class="col s4 left-align">
              <input
                @change="handleChangeAccords($event)"
                type="checkbox"
                id="Piano-accord"
                value="piano:accord:1"
                name="piano"
                v-model="accords.piano"
              >
              <label for="Piano-accord">Piano</label>
            </div>
            <div class="col s12 left-align">
              <input
                @change="handleChangeAccords($event)"
                type="checkbox"
                id="trumpet-accord"
                value="trumpet:accord:57"
                name="trumpet"
                v-model="accords.trumpet"
              >
              <label for="trumpet-accord">trumpet</label>
            </div>
            <div class="col s12 left-align">
              <input
                @change="handleChangeAccords($event)"
                type="checkbox"
                id="saxophone-accord"
                name="saxophone"
                value="saxophone:accord:65"
                v-model="accords.saxophone"
              >
              <label for="saxophone-accord">saxophone</label>
            </div>
            <div class="col s12 left-align">
              <input
                @change="handleChangeAccords($event)"
                type="checkbox"
                id="guitar-accord"
                name="guitar"
                value="guitar:accord:25"
                v-model="accords.guitar"
              >
              <label for="guitar-accord">guitar</label>
            </div>
            <div class="col s12 left-align">
              <input
                @change="handleChangeAccords($event)"
                type="checkbox"
                id="bass-accord"
                name="bass"
                value="bass:accord:33"
                v-model="accords.bass"
              >
              <label for="bass-accord">Bass</label>
            </div>
          </div>

          <div v-if="style" class="col s4">
            <h4 class="left-align">Arpeggio</h4>
            <div class="col s12 left-align">
              <input
                @change="handleChangeArpege($event)"
                type="checkbox"
                id="piano-arpege"
                value="piano:arpege:1"
                name="piano"
                v-model="arpeges.piano"
              >
              <label for="piano-arpege">Piano</label>
            </div>
            <div class="col s12 left-align">
              <input
                @change="handleChangeArpege($event)"
                type="checkbox"
                id="trumpet-arpege"
                name="trumpet"
                value="trumpet:arpege:57"
                v-model="arpeges.trumpet"
              >
              <label for="trumpet-arpege">Trumpet</label>
            </div>
            <div class="col s12 left-align">
              <input
                @change="handleChangeArpege($event)"
                type="checkbox"
                name="saxophone-arpege"
                id="saxophone-arpege"
                value="saxophone:arpege:65"
                v-model="arpeges.saxophone"
              >
              <label for="saxophone-arpege">Saxophone</label>
            </div>
            <div class="col s12 left-align">
              <input
                @change="handleChangeArpege($event)"
                type="checkbox"
                name="guitar-arpege"
                id="guitar-arpege"
                value="guitar:arpege:25"
                v-model="arpeges.guitar"
              >
              <label for="guitar-arpege">Guitar</label>
            </div>
            <div class="col s12 left-align">
              <input
                @change="handleChangeArpege($event)"
                type="checkbox"
                name="bass-arpege"
                id="bass-arpege"
                value="bass:arpege:33"
                v-model="arpeges.bass"
              >
              <label for="bass-arpege">Bass</label>
            </div>
          </div>

          <div class="col s4" v-if="style">
            <h4 class="left-align">Drums</h4>
            <div class="switch left-align">
              <label>
                Off
                <input v-model="drums" type="checkbox">
                <span class="lever"></span>
                On
              </label>
            </div>
          </div>
        </div>

        <div v-if="style" class="row">
          <div class="col s8 offset-s1">
            <input v-model="bpm" @change="onBPMChange" type="range" id="test5" min="60" max="150">
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
import instruments from "../../../src/assets/data/instruments";
import playerModel from "../models/playerModel";

export default {
  name: "BardeSettings",
  props: [
    "onStyleChange",
    "onDrumsChange",
    "onBPMChange",
    "onInstrumentChange"
  ],
  data() {
    return {
      instruments: instruments,
      accords: {},
      arpeges: {},
      Player: playerModel,
      style: null,
      drums: false,
      bpm: 120
    };
  },
  watch: {
    style: function(val) {
      this.onStyleChange(val);
    },
    drums: function(val) {
      this.onDrumsChange(val);
    }
    /* bpm: function(val) {
      console.log(val);
      this.onBPMChange(val);
    }
 */
  },
  methods: {
    styleChanged: function() {
      this.onStyleChange();
    },
    handleChangeAccords: function(e) {
      const name = e.target.name;
      const value = e.target.value;
      if (this.accords[name]) {
        Object.keys(this.accords).map(key => {
          if (key != name) {
            //  this.accords[key] = false;
          } else {
            this.onInstrumentChange(value, true);
          }
        });
      } else {
        this.onInstrumentChange(value, false);
      }
    },

    handleChangeArpege: function(e) {
      const name = e.target.name;
      const value = e.target.value;
      if (this.arpeges[name]) {
        Object.keys(this.arpeges).map(key => {
          if (key != name) {
            //  this.accords[key] = false;
          } else {
            this.onInstrumentChange(value, true);
          }
        });
      } else {
        //  console.log("no more ", name, " ", value);
        this.onInstrumentChange(value, false);
      }
    }
  }
};
</script>

<style>
[type="radio"]:not(:checked) + span,
[type="radio"]:checked + span {
  position: relative;
  padding-left: 35px;
  cursor: pointer;
  display: inline-block;
  height: 25px;
  line-height: 25px;
  font-size: 1rem;
  -webkit-transition: 0.28s ease;
  transition: 0.28s ease;
  -webkit-user-select: none;
  -moz-user-select: none;
  -ms-user-select: none;
  user-select: none;
}

[type="radio"] + span:before,
[type="radio"] + span:after {
  content: "";
  position: absolute;
  left: 0;
  top: 0;
  margin: 4px;
  width: 16px;
  height: 16px;
  z-index: 0;
  -webkit-transition: 0.28s ease;
  transition: 0.28s ease;
}

[type="radio"]:not(:checked) + span:before,
[type="radio"]:not(:checked) + span:after,
[type="radio"]:checked + span:before,
[type="radio"]:checked + span:after,
[type="radio"].with-gap:checked + span:before,
[type="radio"].with-gap:checked + span:after {
  border-radius: 50%;
}

[type="radio"]:not(:checked) + span:before,
[type="radio"]:not(:checked) + span:after {
  border: 2px solid #5a5a5a;
}

[type="radio"]:not(:checked) + span:after {
  -webkit-transform: scale(0);
  transform: scale(0);
}

[type="radio"]:checked + span:before {
  border: 2px solid transparent;
}

[type="radio"]:checked + span:after,
[type="radio"].with-gap:checked + span:before,
[type="radio"].with-gap:checked + span:after {
  border: 2px solid #26a69a;
}

[type="radio"]:checked + span:after,
[type="radio"].with-gap:checked + span:after {
  background-color: #26a69a;
}

[type="radio"]:checked + span:after {
  -webkit-transform: scale(1.02);
  transform: scale(1.02);
}

[type="radio"].with-gap:checked + span:after {
  -webkit-transform: scale(0.5);
  transform: scale(0.5);
}

[type="radio"].tabbed:focus + span:before {
  -webkit-box-shadow: 0 0 0 10px rgba(0, 0, 0, 0.1);
  box-shadow: 0 0 0 10px rgba(0, 0, 0, 0.1);
}

[type="radio"].with-gap:disabled:checked + span:before {
  border: 2px solid rgba(0, 0, 0, 0.42);
}

[type="radio"].with-gap:disabled:checked + span:after {
  border: none;
  background-color: rgba(0, 0, 0, 0.42);
}

[type="radio"]:disabled:not(:checked) + span:before,
[type="radio"]:disabled:checked + span:before {
  background-color: transparent;
  border-color: rgba(0, 0, 0, 0.42);
}

[type="radio"]:disabled + span {
  color: rgba(0, 0, 0, 0.42);
}

[type="radio"]:disabled:not(:checked) + span:before {
  border-color: rgba(0, 0, 0, 0.42);
}

[type="radio"]:disabled:checked + span:after {
  background-color: rgba(0, 0, 0, 0.42);
  border-color: #949494;
}
</style>

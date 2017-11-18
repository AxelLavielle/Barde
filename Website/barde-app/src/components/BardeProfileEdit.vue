<template>
  <div class="barde-main-dashboard">
    <div class="container">
      <h5 class="left-align">Edit Profile</h5>
      <div class="row">
        <form class="col s12">
          <div class="row">
            <div class="input-field col s12">
              <input v-model="user.name.userName" id="username" type="text" class="validate">
              <label for="username">Username</label>
            </div>
          </div>
          <div class="row">
            <div class="input-field col s12">
              <input v-model="user.email" id="email" type="email" class="validate">
              <label for="email">Email</label>
            </div>
          </div>
          <div class="row">
            <div class="input-field col s6">
              <input v-model="user.name.firstName" id="firstname" type="text" class="validate">
              <label for="firstname">Firstname</label>
            </div>
            <div class="input-field col s6">
              <input v-model="user.name.lastName" id="lastname" type="text" class="validate">
              <label for="lastname">Lastname</label>
            </div>
          </div>
          <div class="row">
            <a class="waves-effect waves-light btn white pink-text">Cancel</a>

            <a v-on:click="updateUser()" class="waves-effect waves-light btn pink"><i class="material-icons right">save</i>Save</a>
          </div>
        </form>
      </div>
    </div>
  </div>
</template>

<script>
  import BardeProfileSidePanel from '@/components/BardeProfileSidePanel.vue'
  import '../assets/js/BardeRegister'

  import '../../static/css/player.css'

  export default {
    components: {
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
          console.log(this.$http.options.root)
        }
      },
      getUser(){
        var jwtDecode = require('jwt-decode');
        this.user = jwtDecode(this.$auth.token('default'));
      },
      updateUser(){
        console.log(this.$http.options.root)

        this.$http.post('/user', this.user).then(function (res){
        })
      }
    },
    beforeMount(){
      this.getUser();
    }
  }
</script>


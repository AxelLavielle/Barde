<template>
   <div class="left-panel">
      <h5>Menu</h5>
      <div class="img-profile">
        <img src="../../static/img/barde-logo.png" class="responsive-img" alt="user profile ">
      </div>
      <div class="profile-infos">
        <span class="username">{{user.name.userName}}</span>
      </div>
      <div class="row">
        <div class="navigation">
          <div class="row">
            <div class="input-field s12 align-center">
              <a href="#/home" class="waves-effect waves-light pink btn"><i class="material-icons right">home</i>Home</a>
            </div>
            <div class="input-field s12 align-center">
            <a href="#/settings" class="waves-effect waves-light pink btn"><i class="material-icons right">settings</i>settings</a>
            </div>
            <div class="input-field s12">
              <a v-on:click="logout()" class="waves-effect waves-light pink btn"><i class="material-icons right">exit_to_app</i>Logout</a>
            </div>
          </div>
        </div>
      </div>
   </div>
</template>

<script>

  import '../assets/js/BardeRegister'


  export default {
    name: 'BardeProfileSidePanel',
    data () {
      return {
        user:{}
      }
    },
    methods :{
      getUser(){
        var jwtDecode = require('jwt-decode');
        this.user = jwtDecode(this.$auth.token('default'));
      },
      logout(){
        this.$auth.token('default', '');

        this.$auth.logout();
      }
    },
    beforeMount(){
      this.getUser();
    }
  }
</script>


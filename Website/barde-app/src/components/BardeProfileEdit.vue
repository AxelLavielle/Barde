<template>
  <div class="barde-main-dashboard">
    <div class="container">
      <h5 class="left-align">Edit Profile</h5>
      <div class="row">
        <form class="col s12">
          <div class="row">
            <div class="input-field col s12">
              <input v-model="form.username" id="username" type="text" class="validate">
              <label for="username">Username</label>
            </div>
          </div>
          <div class="row">
            <div class="input-field col s12">
              <input v-model="form.email" id="email" type="email" class="validate">
              <label for="email">Email</label>
            </div>
          </div>
          <div class="row">
            <div class="input-field col s6">
              <input v-model="form.firstName" id="firstname" type="text" class="validate">
              <label for="firstname">Firstname</label>
            </div>
            <div class="input-field col s6">
              <input v-model="form.lastName" id="lastname" type="text" class="validate">
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

  import '../../static/css/player.css'

  export default {
    components: {
      BardeProfileSidePanel
    },
    name: 'HelloWorld',
    data () {
      return {
        user : {},
        form : {
          'username' : "",
          'email' : "",
          'firstName' : "",
          'lastName' : ""
        }
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

        this.$http.get('user/me', {
          headers: {
            Authorization: this.$auth.token('default')
          }
        }).then(function (res){
          this.user = res.body.data.user;


          this.form.username = res.body.data.user.name.userName;
          this.form.email = res.body.data.user.email;
          this.form.firstName = res.body.data.user.name.firstName;
          this.form.lastName = res.body.data.user.name.lastName;


        });


      },
      updateUser(){


        this.$http.patch('user', this.form, {
          headers: {
            Authorization: this.$auth.token('default')
          }
        }).then(function (res){
          console.log(res);
          Materialize.toast(res.body.msg, 4000, 'green');
        }).catch(function (err){
          Materialize.toast(res.body.msg, 4000, 'red');

        });
      }
    },
    beforeMount(){
      this.getUser();
    },
    mounted(){
      console.log(Materialize);
      $( document ).ready(function() {
        Materialize.updateTextFields();
      });


    }
  }
</script>


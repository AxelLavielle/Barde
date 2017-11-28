<template>
  <div class="container">
    <div class="valign-wrapper">

      <!--   Icon Section   -->
      <div class="row">
        <div class="col m6 s12 valign-wrapper">
          <div class="section section-left">
            <h1 class="header barde-title center pink-text">Barde</h1>
            <h5 class="left-align">Create an account</h5>

            <form  @submit.prevent="register()" class="col s12">
              <div class="row">
                <div class="input-field col s12">
                  <input v-model="user.userName" id="username" type="text" class="validate">
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
                <div class="input-field col s12">
                  <input v-model="user.password" id="password" type="password" class="validate">
                  <label for="password">Password</label>
                </div>
              </div>
              <div class="row">
                <div class="input-field col s6">
                  <input v-model="user.firstName" id="firstname" type="text" class="validate">
                  <label for="firstname">Firstname</label>
                </div>
                <div class="input-field col s6">
                  <input v-model="user.lastName" id="lastname" type="text" class="validate">
                  <label for="lastname">Lastname</label>
                </div>
              </div>
              <div class="row">
                <div class="input-field col s4">
                  <input v-model="user.dayOfBirth" id="dayOfBirth" type="text" class="validate">
                  <label for="firstname">dayOfBirth</label>
                </div>
                <div class="input-field col s4">
                  <input v-model="user.monthOfBirth" id="monthOfBirth" type="text" class="validate">
                  <label for="monthOfBirth">monthOfBirth</label>
                </div>
                <div class="input-field col s4">
                  <input v-model="user.yearOfBirth" id="yearOfBirth" type="text" class="validate">
                  <label for="monthOfBirth">yearOfBirth</label>
                </div>
              </div>
              <div class="row">
                <input type="submit" class="waves-effect waves-light btn pink" value="register">
              </div>
            </form>

            <p class="center-align">Already registred ? <a href="#/login">Login</a></p>

          </div>
        </div>

        <div class="col m6 s12 valign-wrapper">
          <div class="section section-right">
            <p>

              Barde is a multiplatform application for generating procedural surround musics. Our service is aimed at professionals in the tertiary sector but the application will also be available to the general public. The user of Barde will be able in a few clicks to create his musical atmosphere in the style of his choice and Barde will be responsible for generating it indefinitely.
            </p>

          </div>
        </div>

      </div>
    </div>
  </div>
</template>

<script>

  import '../../assets/js/BardeRegister'

  export default {
    name: 'HelloWorld',
    data() {
      return {
        user: {

        }
      }
    },
    methods: {
      register() {
        this.$auth.register({
          body: this.user, // Vue-resoruce
          success: function (res) {

            Materialize.toast(res.data.message, 4000, 'green');
          },
          error: function (res) {
            console.log();

            Materialize.toast(jQuery.parseJSON(res.bodyText).data.message, 4000, 'red');
            this.error = res.data;
          }
        });
      }
    }
  }
</script>


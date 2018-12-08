<template>
  <div class="container">
    <div class="valign-wrapper">
      <!--   Icon Section   -->
      <div class="row">
        <div class="col m6 s12 valign-wrapper">
          <div class="section section-left">
            <h1 class="header barde-title center pink-text">Barde</h1>
            <h5 class="left-align">Create an account</h5>

            <form @submit.prevent="register()" class="col s12">
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
                  <input
                    v-model="user.dayOfBirth"
                    id="dayOfBirth"
                    min="01"
                    max="31"
                    value="1"
                    type="number"
                    class="validate active"
                  >
                  <label for="firstname">Day of birth</label>
                </div>
                <div class="input-field col s4">
                  <input
                    v-model="user.monthOfBirth"
                    id="monthOfBirth"
                    min="01"
                    max="12"
                    type="number"
                    class="validate"
                  >
                  <label for="monthOfBirth">Month of birth</label>
                </div>
                <div class="input-field col s4">
                  <input
                    v-model="user.yearOfBirth"
                    id="yearOfBirth"
                    min="1900"
                    max="2000"
                    type="number"
                    class="validate"
                  >
                  <label for="monthOfBirth">Year of birth</label>
                </div>
              </div>
              <div class="row">
                <div v-if="isFetching" class="preloader-wrapper small active">
                  <div class="spinner-layer spinner-green-only">
                    <div class="circle-clipper left">
                      <div class="circle"></div>
                    </div>
                    <div class="gap-patch">
                      <div class="circle"></div>
                    </div>
                    <div class="circle-clipper right">
                      <div class="circle"></div>
                    </div>
                  </div>
                </div>

                <input
                  v-if="!isFetching"
                  type="submit"
                  class="waves-effect waves-light btn pink"
                  value="register"
                >
              </div>
            </form>

            <p class="center-align">
              Already registred ?
              <a href="#/login">Login</a>
            </p>
          </div>
        </div>

        <div class="col m6 s12 valign-wrapper">
          <div class="section section-right">
            <p>Barde is a multiplatform application for generating procedural surround musics. Our service is aimed at professionals in the tertiary sector but the application will also be available to the general public. The user of Barde will be able in a few clicks to create his musical atmosphere in the style of his choice and Barde will be responsible for generating it indefinitely.</p>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import "../../assets/js/BardeRegister";

export default {
  name: "HelloWorld",
  data() {
    return {
      user: {
        email: "",
        password: "",
        firstName: "",
        lastName: "",
        userName: "",
        dayOfBirth: "01",
        monthOfBirth: "01",
        yearOfBirth: "1900"
      },
      isFetching: false
    };
  },
  methods: {
    register() {
      this.$auth.register({
        body: this.user, // Vue-resoruce
        autoLogin: true,
        rememberMe: true,
        success: function(res) {
          this.isFetching = false;
          Materialize.toast(res.data.message, 4000, "green");
        },
        error: function(res) {
          this.isFetching = false;
          console.log(res);
          Materialize.toast(
            jQuery.parseJSON(res.bodyText).data.message,
            4000,
            "red"
          );
          this.error = res.data;
        }
      });
    }
  }
};
</script>


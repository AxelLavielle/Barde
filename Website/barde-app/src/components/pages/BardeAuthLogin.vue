<template>
  <div class="container">
    <div class="valign-wrapper">
      <!--   Icon Section   -->
      <div class="row">
        <div class="col m6 s12 valign-wrapper">
          <div class="section section-left">
            <h1 class="header barde-title center pink-text">Barde</h1>
            <h5 class="left-align">Login</h5>

            <form @submit.prevent="login()" class="col s12">
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

                <input v-if="!isFetching" type="submit">

                <!--
                <a href="#/home" class="waves-effect waves-light btn pink"><i class="material-icons right">exit_to_app</i>Login</a>
                -->
              </div>
            </form>

            <p class="left-align">
              Not registred ?
              <a href="#/register">Register now.</a>
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
      user: {},
      isFetching: false
    };
  },
  methods: {
    getFormValues() {
      // console.log(this.user)
      this.$auth.login({ body: this.user }).then(function(ok) {
        alert();
      });
    },
    login() {
      this.isFetching = true;
      this.$auth.login({
        body: this.user,

        success: function(res) {
          this.isFetching = false;

          this.$auth.token("default", res.body.data.token);
          this.$auth
            .fetch({
              params: {
                email: this.user.email,
                password: this.user.password
              },
              success: function(success) {
                Materialize.toast(
                  jQuery.parseJSON(success.bodyText).data.message,
                  4000,
                  "red"
                );
                this.error = res.data;
              },
              error: function(error) {
                console.log(error);
                Materialize.toast(
                  jQuery.parseJSON(error.bodyText).data.message,
                  4000,
                  "red"
                );
                this.error = res.data;
              }
            })
            .catch(function(err) {
              //  Materialize.toast("err", 4000, "red");
              Materialize.toast(
                jQuery.parseJSON(err.bodyText).data.message,
                4000,
                "red"
              );
              this.error = res.data;
            });
        },
        error: function(err) {
          Materialize.toast(
            jQuery.parseJSON(err.bodyText).data.message,
            4000,
            "red"
          );
          this.isFetching = false;
        }
      });
    }
  }
};
</script>


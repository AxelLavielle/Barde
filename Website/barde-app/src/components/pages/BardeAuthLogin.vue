<template>
  <div class="container">
    <div class="valign-wrapper">
      <!--   Icon Section   -->
      <div class="row">
        <div class="col m6 s12 valign-wrapper">
          <div class="section section-left">
            <h1 class="header barde-title center pink-text">Barde</h1>
            <h5 class="left-align">Connexion</h5>

            <form @submit.prevent="login()" class="col s12">
              <div class="row">
                <div class="input-field col s12">
                  <input v-model="user.email" id="email" type="email" class="validate">
                  <label for="email">Email</label>
                  <span class="helper-text" data-error="wrong" data-success="right"></span>
                </div>
              </div>
              <div class="row">
                <div class="input-field col s12">
                  <input v-model="user.password" id="password" type="password" class="validate">
                  <label for="password">Mot de passe</label>
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
              Pas de compte ?
              <a href="#/register">S'inscrire ici</a>
            </p>
          </div>
        </div>

        <div class="col m6 s12 valign-wrapper">
          <div class="section section-right">
            <p>Barde est une application multiplateforme de génération de musiques d'ambiance procédurales. Notre service s'adresse aux professionnels du secteur tertiaire mais l'application sera également disponible au grand public. L'utilisateur de Barde pourra en quelques clics créer son ambiance musicale dans le style de son choix et Barde se chargera de la générer indéfiniment.</p>
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
        fetchUser: false,

        success: function(res) {
          this.isFetching = false;

          this.$auth.token("default", res.body.data.token);
        },
        error: function(err) {
          if (err && err.bodyText && err.bodyText) {
            console.log(err);
            Materialize.toast(
              "L'email ou le mot de passe est incorrect",
              4000,
              "red"
            );
          }
          this.isFetching = false;
        }
      });
    }
  }
};
</script>


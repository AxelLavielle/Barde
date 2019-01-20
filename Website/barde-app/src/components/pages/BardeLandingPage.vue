<template>
  <div class="container">
    <div class="valign-wrapper">
      <!--   Icon Section   -->
      <div class="row hide-on-med-and-down" id="barde-landing-page">
        <div class="col m6 s12 valign-wrapper">
          <div class="section section-left">
            <h1 class="header barde-title center pink-text">Barde</h1>

            <div class="input-field col s12">
              <a
                href="#/register"
                class="btn-large waves-effect waves-light white-text pink auth-btn"
              >S'enregistrer</a>
            </div>

            <div class="input-field col s12">
              <p>Déja un compte ?</p>
            </div>
            <div class="input-field col s12">
              <a
                href="#/login"
                class="btn-large waves-effect waves-light pink-text white auth-btn"
              >Login</a>
            </div>
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
export default {
  name: "HelloWorld",
  data() {
    return {};
  },
  mounted() {
    try {
      var jwtDecode = require("jwt-decode");
      let decoded = jwtDecode(this.$auth.token("default")); // valid token format
      this.user = decoded;
      this.$router.push("home");
    } catch (error) {
      //      this.$auth.logout();
    }

    /*  var jwtDecode = require("jwt-decode");
    this.user = jwtDecode(this.$auth.token("default"));
    if (this.user) {
      d;
    } */
  }
};
</script>


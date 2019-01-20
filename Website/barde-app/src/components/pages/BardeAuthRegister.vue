<template>
  <div class="container">
    <div class="valign-wrapper">
      <!--   Icon Section   -->
      <div class="row">
        <div class="col m6 s12 valign-wrapper">
          <div class="section section-left">
            <h1 class="header barde-title center pink-text">Barde</h1>
            <h5 class="left-align">Créer un compte</h5>

            <form @change="checkForm" @submit.prevent="register()" class="col s12">
              <div class="row">
                <div class="input-field col s12">
                  <input
                    required
                    v-model="user.userName"
                    id="username"
                    type="text"
                    class="validate required"
                  >
                  <label for="username">Nom d'utilisateur</label>
                </div>
              </div>
              <div class="row">
                <div class="input-field col s12">
                  <input required v-model="user.email" id="email" type="email" class="validate">
                  <label for="email">Email</label>
                </div>
              </div>
              <div class="row">
                <div class="input-field col s12">
                  <input
                    required
                    v-model="user.password"
                    id="password"
                    type="password"
                    class="validate"
                  >
                  <label for="password">Mot de passe</label>
                </div>
              </div>
              <div class="row">
                <div class="input-field col s12">
                  <input
                    required
                    v-model="Confirmpassword"
                    id="Confirmpassword"
                    type="password"
                    class="validate"
                    v-bind:class="{ valid: user.password == Confirmpassword && user.password.lenght > 0, invalid: user.password !== Confirmpassword}"
                  >
                  <label for="password">Confirmation du mot de passe</label>
                </div>
              </div>
              <div class="row">
                <div class="input-field col s6">
                  <input v-model="user.firstName" id="firstname" type="text" class="validate">
                  <label for="firstname">Prénom</label>
                </div>
                <div class="input-field col s6">
                  <input v-model="user.lastName" id="lastname" type="text" class="validate">
                  <label for="lastname">Nom</label>
                </div>
              </div>
              <div class="row">
                <p>Date de naisance</p>
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
                  <label for="firstname">Jour</label>
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
                  <label for="monthOfBirth">Mois</label>
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
                  <label for="monthOfBirth">Année</label>
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
                  :disabled="!validForm"
                  v-if="!isFetching || validForm"
                  type="submit"
                  class="waves-effect waves-light btn pink"
                  value="register"
                >
              </div>
            </form>

            <p class="center-align">
              Déjà un compte ?
              <a href="#/login">Connectez-vous ici</a>
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
  mounted: () => {
    $(".datepicker").pickadate({
      selectMonths: true, // Creates a dropdown to control month
      selectYears: 100, // Creates a dropdown of 15 years to control year,
      today: "Today",
      clear: "Clear",
      close: "Ok",
      closeOnSelect: true // Close upon selecting a date,
    });
  },
  data() {
    return {
      validForm: false,
      userNameIsValid: false,
      user: {
        email: "",
        password: "",
        firstName: "",
        lastName: "",
        userName: "",
        dayOfBirth: "",
        monthOfBirth: "",
        yearOfBirth: ""
      },
      Confirmpassword: "",

      isFetching: false
    };
  },
  watch: {
    "user.userName": function(val) {
      this.userNameIsValid = this.user.userName.lenght > 0;
    },
    lastName: function(val) {
      this.fullName = this.firstName + " " + val;
    }
  },
  methods: {
    checkForm() {
      console.log(
        "checking form",
        this.user.password,
        this.Confirmpassword,
        this.user.password === this.Confirmpassword
      );
      this.validForm = this.user.password === this.Confirmpassword;
      console.log(this.validForm);
    },
    register() {
      console.log(this.user);
      this.$auth.register({
        body: this.user, // Vue-resoruce

        success: function(res) {
          this.isFetching = false;
          Materialize.toast(res.data.message, 4000, "green");
        },
        error: function(res) {
          this.isFetching = false;

          var message = "";
          switch (jQuery.parseJSON(res.bodyText).data.message) {
            case "The password must have at least one uppercase character.":
              message = "Le mot de passe doit avoir au moins une majuscule.";
              break;
            case "The password must have at least one symbol character.":
              message = "Le mot de passe doit avoir au moins un symbole.";
              break;
            case "The password must have at least one number character.":
              message = "Le mot de passe doit contenir au moins un chiffre";
              break;
            case "The password must have at least eight characters.":
              message =
                "Le mot de passe doit avoir une longueur de 8 characteres minimum";
          }

          console.log(res);
          Materialize.toast(message, 4000, "red");
          this.error = res.data;
        }
      });
    }
  }
};
</script>


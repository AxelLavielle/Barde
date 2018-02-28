import VueRecaptcha from 'vue-recaptcha';

export default {
    name: 'ContactVue',
    data() {
        return {
            "name": "",
            "email": "",
            "message": "",
            "verified" : false,
            sitekey: '6Lf9j0kUAAAAAFmTvmAHXEHG8ir_RaPNj_zaEcqa'

        }
    },
    components: {
        'vue-recaptcha': VueRecaptcha
    },
    mounted: function () {
    },
    methods: {
        onVerify: function (response) {

            var data      = {'response' : response};
            var headers =   {'content-type':"application/json"};

            this.$http.post('captcha/verify', data, headers).then(function (success) {

                this.verified = true;

            });

            },
        onExpired: function () {

        },
        resetRecaptcha () {
            this.$refs.recaptcha.reset() // Direct call reset method
        },
        checkCaptcha(){
            var googleResponse = jQuery('#g-recaptcha-response').val();
            if (googleResponse){


                var data      = {'response' : googleResponse};
                var headers =   {'content-type':"application/json"};

                this.$http.post('captcha/verify', data, headers).then(function (success) {
                    this.verified = true;
                });
            }

        },
        send_email(event) {
            event.preventDefault();

            this.checkCaptcha();

            if (this.verified){
                var data = {'name': this.name, 'email': this.email, 'message' : this.message};
                var headers = {headers: {'content-type': 'application/json'}}

                if (!this.name || !this.email || !this.email){
                    Materialize.toast('All fields are required', "4000", 'red');
                    return;
                }

                this.$http.post('email/send', data, headers).then(function (success) {

                    console.log(success);

                    if (success.status == 200) {
                        Materialize.toast('Message sent!');
                        this.name = "";
                        this.email = "";
                        this.message = "";
                    }

                    if (success.status == 304) {
                        Materialize.toast('You\'re already subscribed!');
                    }
                }, function (error) {
                    Materialize.toast('An error occured');
                });
            }else{
                Materialize.toast('Please use the Recaptcha', "4000", 'red');
            }
        }
    }
}

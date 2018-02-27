export default {
    name: 'ContactVue',
    data() {
        return {
            "name": "",
            "email": "",
            "message": ""
        }
    },
    components: {},
    mounted: function () {

    },
    methods: {
        send_email(event) {
            event.preventDefault();

            var data = {'name': this.name, 'email': this.email, 'message' : this.message};
            var headers = {headers: {'content-type': 'application/json'}}

            this.$http.post('http://localhost:3000/email/send', data, headers).then(function (success) {
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
        }
    }
}

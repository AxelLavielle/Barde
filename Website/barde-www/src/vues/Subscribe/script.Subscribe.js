import Materialize from '../../../node_modules/materialize-css/dist/js/materialize'

export default {
    name: 'SubVue',
    data () {
        return {
            'email' : ""
        }
    },
    components : {
    },
    mounted: function () {

    },
    methods: {
        validEmail:function(email) {
            var re = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
            return re.test(email);
        },
        subscribe(event) {
            event.preventDefault();

            var data      = {'email' : this.email.replace(/\s/g, '') ,'subscribe' : true};
            var headers   =    {headers:{'content-type': 'application/json' }}

            if (!this.validEmail(data.email)){
                Materialize.toast('Invalid email', '4000', 'red');

            }
            else{
            this.$http.put('email', data, headers).then(function (success){


                if (success.body.data.message){
                    Materialize.toast(success.body.data.message, '4000', 'green');
                }

            }, function(error){

                if (error.body.data) {
                    Materialize.toast(error.body.data.message, '4000', 'red');
                } else{
                    Materialize.toast('You are already subscribed', '4000', 'orange');
                }
            });
            }
        }
    }
}
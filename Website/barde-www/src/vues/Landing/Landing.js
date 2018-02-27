import LandingBackground from '../../assets/images/backgrounds/bg-large-2.png'
import BardeLogo from '../../assets/images/logo-4k.png'

import $ from 'jquery'

export default {
    name: 'LandingVue',
    data () {
        return {
            "background" : LandingBackground,
            "logo" : BardeLogo
        }
    },
    components:{

    },
    mounted: function () {
        $('.parallax').parallax();

    },
    methods: {}
}
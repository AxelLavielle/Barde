import LandingVue from '../Landing/Landing.vue'
import AboutVue from '../About/About.vue'
import TeamVue from '../Team/Team.vue'
import LatestNews from '../LatestNews/LatestNews.vue'
import SubVue from '../Subscribe/Subscribe'
import ContactVue from '../Contact/Contact'
import FooterComponent from '../../components/Footer/Footer'

import Materialize from '../../../node_modules/materialize-css/dist/js/materialize'


export default {
    name: 'HomeVue',
    data () {
        return {
        }
    },
    components : {
        LandingVue,
        AboutVue,
        TeamVue,
        LatestNews,
        SubVue,
        ContactVue,
        FooterComponent
    },
    mounted: function () {
        $('.scrollspy').scrollSpy({scrollOffset: 0});
    },
    methods: {}
}
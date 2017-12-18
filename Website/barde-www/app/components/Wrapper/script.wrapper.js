/**
 * APLT
 * < arnaud perrault />
 * barde-www - Created on 27/05/2017
 */

export default {
    name: 'App',
    components: {},
    data () {
        return {
            showMenu: false
        }
    },
    mounted: function () {
        console.log(this.$route)
        if (this.$route.name !== 'home') {
            this.showMenu = true;
        }
        else
            this.showMenu = false;
    },
    methods: {},
}
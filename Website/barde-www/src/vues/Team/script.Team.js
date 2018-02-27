import TeamCard from '../../components/CardTeam/CardTeam'
import TeamData from '../../assets/data/Team'

export default {
    name: 'TeamVue',
    data () {
        return {
            team: TeamData
        }
    },
    components : {
        TeamCard
    },
    mounted: function () {

    },
    methods: {}
}
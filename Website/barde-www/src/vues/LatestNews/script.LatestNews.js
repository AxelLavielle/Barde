import CardNews from '../../components/CardNews/CardNews'
import BlogPosts from '../../assets/data/Blog'

export default {
    name: 'LatestNews',
    data () {
        return {
            posts : BlogPosts.posts
        }
    },
    components : {
        CardNews
    },
    mounted: function () {

    },
    methods: {}
}
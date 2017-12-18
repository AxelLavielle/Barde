/**
 * APLT
 * < arnaud perrault />
 * barde-www - Created on 05/06/2017
 */

import news from './news.js';

function indexWhere(array, conditionFn) {
    const item = array.find(conditionFn)
    return array.indexOf(item)
}

export default {
    name: 'BlogDetail',
    data () {
        return {
            news: news,
            cNews: {}
        }
    },
    mounted: function () {

        console.log(news);

        var newsSlug = this.$route.params.id;

        const cNews = indexWhere(news, item => item.value === newsSlug)

        this.cNews = news[cNews];

    },
    methods: {}
}

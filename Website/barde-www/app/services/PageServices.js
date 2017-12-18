/**
 * APLT
 * < arnaud perrault />
 * barde-www - Created on 27/05/2017
 */

import Vue from 'vue'
import config from '../config';

export default {
    getPage: function(page) {
        return (Vue.http.get(config.apiUrl + '/statics/page/' + page))
    },
    getBanners: function() {
        return (Vue.http.get(config.apiUrl + '/banners'))
    }

}
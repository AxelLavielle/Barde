/**
 * APLT
 * < arnaud perrault />
 * barde-www - Created on 27/05/2017
 */


import Vue from 'vue'
import config from '../config';

export default {
    getRoot: function() {
        return (Vue.http.get(config.apiUrl + '/categories/roots'))
    },
    getChildren: function(id) {
        return (Vue.http.get(config.apiUrl + '/categories/children/' + id))
    }

}
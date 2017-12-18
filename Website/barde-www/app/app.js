/**
 * APLT
 * < arnaud perrault />
 * barde-www - Created on 27/05/2017
 */

import Vue from 'vue'
import VueRouter from 'vue-router'
import VueResource from 'vue-resource'

Vue.use(VueRouter)
Vue.use(VueResource)

const routes = [
    {
        path: '/',
        component: require('./components/Home/home.vue'),
        name: 'home'
    },
    {
        path: '/blog',
        component: require('./components/Blog/blog.vue'),
        name: 'blog'
    },
    {
        path: '/blog/:id',
        component: require('./components/BlogDetail/blog-detail.vue'),
        name: 'blogDetail'
    },
    {
        path: '/team',
        component: require('./components/Team/team.vue'),
        name: 'team'
    },
    {
        path: '/contact',
        component: require('./components/Contact/contact.vue'),
        name: 'contact'
    },
    {
        path: '*',
        redirect: '/'
    }
];

var router = new VueRouter({
    mode: 'history',
    routes
});

var app = new Vue({
    el: '#app',
    router,
    render: h => h(require('./components/Wrapper/wrapper.vue'))
});

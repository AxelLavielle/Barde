import Vue from 'vue'

import VueResource from 'vue-resource'
import VueRouter from 'vue-router'

import Container from './components/Container/Container.vue'

Vue.config.productionTip = false

Vue.use(VueRouter);
Vue.use(VueResource);

console.log(process.env.NODE_ENV)

const routes = [
    {
        path: '/',
        component: require('./vues/Home/Home.vue').default,
        name: 'home'
    },
    {
        path: '/blog',
        component: require('./vues/Blog/Blog.vue').default,
        name: 'blog'
    },
    {
        path: '/blog/last-steps',
        component: require('./vues/SinglePost/SinglePost.vue').default,
        name: 'last-steps'
    },
    {
        path: '*',
        redirect: '/'
    }
];

Vue.http.options.root = process.env.NODE_ENV === 'development' ? 'http://api-dev.barde.io' : 'http://api.barde.io';

var router = new VueRouter({
    mode: 'history',
    routes
});

new Vue({
    router,
    render: h => h(Container)
}).$mount('#app')

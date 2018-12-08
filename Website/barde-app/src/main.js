// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import App from './App'
import VueResource from 'vue-resource'
import Router from 'vue-router'
import router from './router'

Vue.use(Router)
Vue.use(VueResource)

Vue.router = router

Vue.use(require('@websanova/vue-auth'), {
  router: require('@websanova/vue-auth/drivers/router/vue-router.2.x'),
  auth: require('@websanova/vue-auth/drivers/auth/bearer'),
  http: require('@websanova/vue-auth/drivers/http/vue-resource.1.x'),
  fetchData: { url: 'user/me', method: 'GET', enabled: true },
  loginData: { url: 'auth/login', method: 'POST', redirect: '/home', fetchUser: false }
})

Vue.http.options.emulateJSON = true

Vue.http.options.root = process.env.NODE_ENV === 'development' ? 'http://163.172.191.206:2101' : 'https://api.barde.io'

/* eslint-disable no-new */
var vm = new Vue({
  el: '#app',
  router,
  template: '<App/>',
  components: { App }
})

global.vm = vm

vm.$on('play', function (data) {})

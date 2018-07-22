import Vue from 'vue'
import Router from 'vue-router'

import BardeLandingPage from '@/components/pages/BardeLandingPage'
import BardeAuthRegister from '@/components/pages/BardeAuthRegister'
import BardeAuthLogin from '@/components/pages/BardeAuthLogin'
import BardeHome from '@/components/pages/BardeHome'
import BardeSettings from '@/components/pages/BardeSettings'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'BardeLandingPage',
      component: BardeLandingPage
    },
    {
      path: '/register',
      name: 'BardeAuthRegister',
      component: BardeAuthRegister
    },
    {
      path: '/login',
      name: 'BardeAuthLogin',
      component: BardeAuthLogin
    },
    {
      path: '/home',
      name: 'BardeHome',
      component: BardeHome
    },
    {
      path: '/settings',
      name: 'BardeSettings',
      component: BardeSettings
    }
  ]
})

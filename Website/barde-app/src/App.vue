<template>
  <div id="app">
    <div v-if="$auth.ready()">
      <router-view></router-view>
    </div>

    <div v-if="!$auth.ready()">
      Loading ...
    </div>    </div>
</template>

<script>

  import 'materialize-css/dist/css/materialize.min.css'
  import 'materialize-css/dist/js/materialize.min'
  import '../static/css/barde.css'

  export default {
  name: 'app'
}
</script>

<style>
</style>

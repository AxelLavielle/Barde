angular.module('app', ['ngRoute', 'app.directives', 'app.controllers', 'ngCookies', 'vcRecaptcha', 'ui.materialize']);

angular.module('app', ['app.controllers', 'ngRoute']).config(function($routeProvider, $locationProvider) {


        $routeProvider


    .when("/",
    {
      templateUrl   : "templates/home.tpl.htm",
      controller    : "mainController"
    })
    .when("/accueil",
    {
      templateUrl   : "templates/home.tpl.htm",
      controller    : "mainController"
    })
    .when("/equipe",
    {
      templateUrl   : "templates/equipe.tpl.htm",
      controller    : "teamController"
    })
    .when("/blog",
    {
      templateUrl   : "templates/blog.tpl.htm",
      controller    : "mainController"
    })
    .when("/contact",
    {
      templateUrl   : "templates/contact.tpl.htm",
      controller    : "mainController"
    })
    .otherwise({templateUrl: 'templates/static/404.tpl.htm'});

}).config(function ($httpProvider) {
  $httpProvider.defaults.withCredentials = false;
  $httpProvider.defaults.headers.put = {};
  $httpProvider.defaults.headers.patch = {};
  $httpProvider.defaults.useXDomain = true;


});

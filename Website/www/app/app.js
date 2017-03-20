angular.module('app', ['app.factories', 'app.directives', 'app.controllers', 'ngRoute']).config(function($routeProvider) {

    $routeProvider
    .when("/",
    {
      templateUrl   : "templates/home.tpl.htm",
      controller    : 'mainController'
    })
    .when("/home",
    {
      templateUrl   : "templates/home.tpl.htm",
      controller    : 'mainController'
    })
    .when("/team",
    {
      templateUrl   : "templates/equipe.tpl.htm",
      controller    : 'teamController'
    })
    .when("/blog",
    {
      templateUrl   : "templates/blog.tpl.htm",
      controller    : 'mainController'
    })
    .when("/contact",
    {
      templateUrl   : "templates/contact.tpl.htm",
      controller    : 'contactController'
    })
    .otherwise({templateUrl: 'templates/static/404.tpl.htm'});

}).config(function ($httpProvider) {
  $httpProvider.defaults.withCredentials = false;
  $httpProvider.defaults.headers.put = {};
  $httpProvider.defaults.headers.patch = {};
  $httpProvider.defaults.useXDomain = true;
});

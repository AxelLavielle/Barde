angular.module('app', ['app.factories', 'app.directives', 'app.controllers', 'ngRoute', 'angular-google-analytics']).config(function($routeProvider) {

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

}).config(function ($httpProvider, AnalyticsProvider) {
  $httpProvider.defaults.withCredentials = false;
  $httpProvider.defaults.headers.put = {};
  $httpProvider.defaults.headers.patch = {};
  $httpProvider.defaults.useXDomain = true;
  AnalyticsProvider.setAccount('UA-91271933-1');  //UU-XXXXXXX-X should be your tracking code

}).run(['Analytics', function (Analytics) {

}]);

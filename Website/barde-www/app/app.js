angular.module('app', ['app.factories', 'app.directives', 'app.controllers', 'ngRoute', 'angular-google-analytics']).config(function($routeProvider) {

    $routeProvider
    .when("/",
    {
      templateUrl   : "templates/home.tpl.htm",
      controller    : 'mainController',
      type          : 'page',
        meta          : {
        title         : "Barde",
        description   : "Barde is a software/application that generate piped music for your evenings, waiting rooms, dinners, sport sessions or work."
      }
    })
    .when("/home",
    {
      templateUrl   : "templates/home.tpl.htm",
      controller    : 'mainController',
        type          : 'page',
        meta          : {
        title         : "Barde",
        description   : "Barde is a software/application that generate piped music for your evenings, waiting rooms, dinners, sport sessions or work."
      }
    })
    .when("/team",
    {
      templateUrl   : "templates/equipe.tpl.htm",
        type          : 'page',
        meta          : {
        title         : "Barde - Team",
        description   : "Who are we ?"
      }
    })
    .when("/blog",
    {
      templateUrl   : "templates/blog.tpl.htm",
        type          : 'article',
        meta          : {
        title         : "Barde - Blog",
        description   : "First steps ..."
      }
    })
    .when("/contact",
    {
      templateUrl   : "templates/contact.tpl.htm",
        type          : 'page',

        controller    : 'contactController',
      meta          : {
        title         : "Barde - Contact",
        description   : "How to reach us"
      }
    })
    .otherwise({templateUrl: 'templates/static/404.tpl.htm'});

}).config(function ($httpProvider, AnalyticsProvider) {
  $httpProvider.defaults.withCredentials = false;
  $httpProvider.defaults.headers.put = {};
  $httpProvider.defaults.headers.patch = {};
  $httpProvider.defaults.useXDomain = true;
  AnalyticsProvider.setAccount('UA-91271933-1');  //UU-XXXXXXX-X should be your tracking code

}).run(['Analytics', function (Analytics) {}])

.run(['$rootScope', '$route', function($rootScope, $route) {
    $rootScope.$on('$routeChangeSuccess', function() {
        document.title = $route.current.meta.title;
        document.description = $route.current.meta.desc;


    });
}]);

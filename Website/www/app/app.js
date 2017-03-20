angular.module('app', ['ngRoute', 'app.directives', 'app.controllers', 'ngCookies', 'vcRecaptcha', 'ui.materialize']);

angular.module('app', ['app.controllers', 'ngRoute', 'app.directives', 'angular-google-analytics']).config(function ($routeProvider, $locationProvider) {


    $routeProvider


        .when("/",
            {
                templateUrl: "templates/home.tpl.htm",
                controller: "mainController"
            })
        .when("/accueil",
            {
                templateUrl: "templates/home.tpl.htm",
                controller: "mainController"
            })
        .when("/equipe",
            {
                templateUrl: "templates/equipe.tpl.htm",
                controller: "teamController"
            })
        .when("/blog",
            {
                templateUrl: "templates/blog.tpl.htm",
                controller: "mainController"
            })
        .when("/contact",
            {
                templateUrl: "templates/contact.tpl.htm",
                controller: "mainController"
            })
        .otherwise({templateUrl: 'templates/static/404.tpl.htm'});

}).config(['$httpProvider', 'AnalyticsProvider', function ($httpProvider, AnalyticsProvider) {

    $httpProvider.defaults.withCredentials = false;
    $httpProvider.defaults.headers.put     = {};
    $httpProvider.defaults.headers.patch   = {};
    $httpProvider.defaults.useXDomain      = true;

    AnalyticsProvider.setAccount('UA-91271933-1');  //UU-XXXXXXX-X should be your tracking code


}]).run(['Analytics', function (Analytics) {
}]);


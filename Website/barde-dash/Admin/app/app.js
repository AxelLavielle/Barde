angular.module('BardeBo', [
    'ngRoute',
    'ngAnimate',
    'ngTouch',
    'ui.bootstrap',

    'dashboard'
])

    .constant('VERSION', '1.0')

    .run(['VERSION', '$rootScope', '$location', function (VERSION, $rootScope, $location) {

        console.log("APLT Site loaded : ", $rootScope);
        console.log(VERSION);

    }]);

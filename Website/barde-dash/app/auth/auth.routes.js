/**
 * APLT
 * < arnaud perrault />
 * barde-dash - Created on 16/03/2017
 */

var AuthRoutes = angular.module('auth.routes', ['ngRoute']);

AuthRoutes.config([
    '$routeProvider',

    function ($routeProvider) {

        $routeProvider
            .when('/login', {
                controller: 'AuthLoginCtrl',
                templateUrl: 'app/auth/views/auth.login.html',

            });

        //$routeProvider.otherwise('/', {});
    }])
/**
 * APLT
 * < arnaud perrault />
 * barde-backoffice - Created on 17/03/2017
 */

var MainRoutes = angular.module('main.routes', ['ngRoute']);

MainRoutes.config([
    '$routeProvider',

    function ($routeProvider) {

        $routeProvider
            .when('/Main/', {
                controller: 'Ctrl',
                templateUrl: 'app/Main/views/ex.Main.html',

            });

        //$routeProvider.otherwise('/', {});
    }])
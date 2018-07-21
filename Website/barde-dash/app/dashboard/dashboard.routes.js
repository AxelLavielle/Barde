/**
 * APLT
 * < arnaud perrault />
 * Admin - Created on 13/03/2017
 */

var DasboardRoutes = angular.module('dashboard.routes', ['ngRoute']);

DasboardRoutes.config([
    '$routeProvider',

    function ($routeProvider) {

        $routeProvider
            .when('/', {
                controller: 'Ctrl',
                templateUrl: 'app/dashboard/views/dashboard.home.html',

            });

        //$routeProvider.otherwise('/', {});
    }])
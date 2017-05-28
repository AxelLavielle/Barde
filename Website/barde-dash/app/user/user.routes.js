/**
 * APLT
 * < arnaud perrault />
 * barde-dash - Created on 13/03/2017
 */

var UserRoutes = angular.module('user.routes', ['ngRoute']);

UserRoutes.config([
    '$routeProvider',

    function ($routeProvider) {

        $routeProvider
            .when('/user', {
                controller: 'Ctrl',
                templateUrl: 'app/user/views/user.home.html',
                resolve: {
                    isadmin: isAdmin,
                },
            });

        //$routeProvider.otherwise('/', {});
    }])
/**
 * APLT
 * < arnaud perrault />
 * barde-dash - Created on 17/03/2017
 */

var MainControllers = angular.module('main.controllers', []);

MainControllers.controller('MenuCtrl', [
        '$scope',
        '$location',
        '$rootScope',
        '$http',
        'AuthService',
        function ($scope,
                  $location,
                  $rootScope,
                  $http,
                  AuthService) {

            $scope.isAuth = function () {

                return !$rootScope.isConnected;
            }

            $scope.logout = function () {
                console.log("ok")
                AuthService.logout(function () {
                    window.location = "/"
                }, function () {
                    alert("Failed to logout!");
                });
            };

        }
    ]
);

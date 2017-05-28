/**
 * APLT
 * < arnaud perrault />
 * barde-dash - Created on 13/03/2017
 */

var UserControllers = angular.module('user.controllers', []);

UserControllers.controller('Ctrl', [
        '$scope',
        '$location',
        '$rootScope',
        '$http',
        'UserService',
        function ($scope,
                  $location,
                  $rootScope,
                  $http,
                  UserService) {

            $scope.users = {
                count: 0,
                data: {}
            }

            var getNumber = function() {
                UserService.getNumber(function(resp) {
                    console.log(resp);
                    $scope.users.count = resp.data;
                }, function() {
                    $scope.users.count = 0;
                })
            }

            getNumber();

        }
    ]
);

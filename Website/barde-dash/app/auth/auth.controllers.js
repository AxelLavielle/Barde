/**
 * APLT
 * < arnaud perrault />
 * barde-dash - Created on 16/03/2017
 */

var AuthControllers = angular.module('auth.controllers', []);

AuthControllers.controller('AuthLoginCtrl', [
        '$scope',
        '$location',
        '$rootScope',
        '$http',
        'AuthService',
        '$window',
        '$rootScope',
        'md5',
        function ($scope,
                  $location,
                  $rootScope,
                  $http,
                  AuthService,
                  $window,
                  $rootScope,
                  md5) {


            $scope.login = {
                email: "",
                password: ""
            }

            $scope.login = function () {

                var formData = {
                    email: $scope.login.email,
                    password: md5.createHash($scope.login.password)
            }

                AuthService.login(formData, authSuccess, authError);
            };


            var authSuccess = function (res) {
                $rootScope.isConnected = true;
                $window.localStorage.setItem("token", res.data.data.token);
                $location.path('/');

            }

            var authError = function (res) {
                alert(res);
            }

        }
    ]
);

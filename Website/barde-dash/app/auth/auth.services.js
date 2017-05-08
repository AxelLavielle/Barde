/**
 * APLT
 * < arnaud perrault />
 * barde-dash - Created on 16/03/2017
 */

var AuthServices = angular.module('auth.services', []);

AuthServices.service('AuthService',
    ['$q', '$http', '$window', 'AppConfig',
        function ($q, $http, $window, AppConfig) {

            var login = function (data, success, error) {
                return $q(function (resolve, reject) {
                    $http.post(AppConfig.API_URL + '/auth/login', data).then(success, error)
                });
            }

            return {
                login: login,
                logout: function (success) {
                    $window.localStorage.removeItem("token");
                    success();
                }
            };
        }
    ]
)
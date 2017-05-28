/**
 * APLT
 * < arnaud perrault />
 * barde-dash - Created on 13/03/2017
 */

var UserServices = angular.module('user.services', []);

UserServices.service('UserServices',
    ['$q', '$http',
        function ($q, $http) {

            var varExample = false;

            var functionExample = function () {
                console.log(user + "functionExample");
            };

            var getNumber = function (data, success, error) {
                return $q(function (resolve, reject) {
                    $http.get(AppConfig.API_URL + '/user/count').then(success, error)
                });
            }

            var getByPage = function (data, success, error) {
                return $q(function (resolve, reject) {
                    $http.get(AppConfig.API_URL + '/user/' + data.perPage + '/' + data.page).then(success, error)
                });
            }

            return {
                getNumber: getNumber,
                getByPage: getByPage,
                varExample: function () {
                    return varExample;
                },

            };
        }
    ]
)
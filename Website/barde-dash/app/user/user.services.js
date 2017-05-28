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


            return {
                functionExample: functionExample,
                varExample: function () {
                    return varExample;
                },

            };
        }
    ]
)
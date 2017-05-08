/**
 * APLT
 * < arnaud perrault />
 * barde-dash - Created on 17/03/2017
 */

var MainServices = angular.module('main.services', []);

MainServices.service('MainService',
    ['$q', '$http',
        function ($q, $http) {

            var varExample = false;

            var functionExample = function () {
                console.log(Main + "functionExample");
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
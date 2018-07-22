/**
 * APLT
 * < arnaud perrault />
 * Admin - Created on 13/03/2017
 */

var DashboardServices = angular.module('dashboard.services', []);

DashboardServices.service('DashboardService',
    ['$q', '$http',
        function ($q, $http) {

            var varExample = false;

            var functionExample = function () {
                console.log(Dashboard + "functionExample");
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
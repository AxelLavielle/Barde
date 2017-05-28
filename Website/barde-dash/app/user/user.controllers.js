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
        'UserServices',
        function ($scope,
                  $location,
                  $rootScope,
                  $http,
                  UserServices) {

            $scope.pageOptions = {
                perPage: 10,
                pageNumber: 1,
                currentPage: 1
            }

            $scope.users = {
                count: 0,
                data: [{}]
            }

            var getNumber = function () {
                UserServices.getNumber(function (res) {
                    $scope.users.count = Math.max(0, res.data.data.count);
                    $scope.pageNumber  = $scope.users.count / $scope.pageOptions.perPage;
                    console.log($scope.pageNumber);

                }, function () {
                    $scope.users.count = 0;
                })

            };

            var getByPage = function () {

                var data = {
                    perPage: $scope.pageOptions.perPage,
                    page: $scope.pageOptions.currentPage - 1
                }

                UserServices.getByPage(data, function (res) {
                    console.log(res);
                    $scope.users.data = res.data.data.users
                }, function () {
                    console.log(res);
                });

            }

            getByPage();
            getNumber();

        }
    ]
);

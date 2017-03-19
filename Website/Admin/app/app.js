/**
 * APLT
 * < arnaud perrault />
 * barde-backoffice - Created on 13/03/2017
 */


angular.module('barde-backoffice', [
    'ngRoute',
    'ngAnimate',
    'ngTouch',
    'ui.bootstrap',
    'ngStorage',
    'ngMd5',

    'main',
    'dashboard',
    'auth'
])

    .constant('VERSION', '1.0')

    .run(['VERSION', '$rootScope', '$location', function (VERSION, $rootScope, $location) {

        console.log("BARDE-BACKOFFICE Site loaded : ", $rootScope);
        console.log(VERSION);

    }])
    .config(['$locationProvider', '$httpProvider', function ($locationProvider, $httpProvider) {

        $locationProvider.hashPrefix('');


        $httpProvider.interceptors.push(['$q', '$location', '$window', function ($q, $location, $window) {
            return {
                'request': function (config) {
                    config.headers = config.headers || {};
                    var token      = $window.localStorage.getItem("token");

                    console.log(token);
                    if (token) {
                        config.headers.Authorization = token;
                    }
                    return config;
                },
                'responseError': function (response) {
                    if (response.status === 401 || response.status === 403) {
                        $location.path('/login');
                    }
                    return $q.reject(response);
                }
            };
        }]);

    }]);


var isAuthenticate = function ($q, $timeout, $http, $location, $rootScope, $window, AppConfig) {

    var deferred = $q.defer();

    $http.get(AppConfig.API_URL + '/auth/isAuthenticate').then(function (user) {

        if (user.data) {
            $rootScope.isConnected = true;
            $timeout(deferred.resolve, 0);
        }
        // Not Authenticated
        else {
            $rootScope.isConnected = false;
            $timeout(function () {
                deferred.reject();
            }, 0);
            $window.location.href = "#/login";
        }
    });

    return deferred.promise;
};

var isAdmin = function ($q, $timeout, $http, $location, $rootScope, $window, AppConfig) {

    var deferred = $q.defer();

    $http.get(AppConfig.API_URL + '/auth/isAdmin').then(function (res) {

        console.log("isAdmin >>", res);

        if (res.status === 200) {
            $rootScope.isConnected = true;
            $timeout(deferred.resolve, 0);
        }
        else {
            $rootScope.isConnected = false;
            $timeout(function () {
                deferred.reject();
            }, 0);
            $window.location.href = "#/login";
        }
    });

    return deferred.promise;
};


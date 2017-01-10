'use strict';

// Declare app level module which depends on views, and components
angular.module('barde', [
  'ngRoute',
  'barde.home'
]).
config(['$locationProvider', '$routeProvider', function($locationProvider, $routeProvider) {
  $routeProvider.otherwise({redirectTo: '/home'});
}]);

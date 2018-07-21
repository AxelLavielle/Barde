angular.module('BardeBo')
    .constant('AppConfig', {})
    .config(['$locationProvider', function ($locationProvider) {
        $locationProvider.hashPrefix('');
    }]);

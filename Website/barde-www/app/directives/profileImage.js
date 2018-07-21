angular.module('app.directives').directive('profileImage', ['$rootScope', function($rootScope) {

  return {
     restrict: 'E',
     replace: false,
     templateUrl : 'templates/directives/profileImage.htm',
     scope: {
       src: '=',
     },
  link: function (scope, elem, attr) {
    scope.profil = attr.profil;

    scope.load = true;
    scope.img = false;

     var img = elem.find('img');

      img.bind('load', function () {
         scope.load = false;
         scope.img = true;
         scope.$apply();
       });

   },

}

}]);

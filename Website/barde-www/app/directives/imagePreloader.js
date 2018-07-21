angular.module('app.directives').directive('imagePreloader', ['$rootScope', function($rootScope) {

  return {
     restrict: 'E',
     replace: false,
     templateUrl : 'templates/directives/imagePreloader.htm',
     scope: {
       src: '=',
     },
  link: function (scope, elem, attr) {
    scope.load = true;
    scope.src = attr.src;
     var img = elem.find('img');
      img.bind('load', function () {
         scope.load = false;
        scope.img = true;
         scope.$apply();
       });

   },
}

}]);

angular.module('app.directives',[]);


angular.module('app.directives').directive('bardeTranslation', function($compile){

  return {
    restrict: 'A',
    template: '{{data}}',
    scope: {
        data: '=',
    },
    link : function(scope, element, attrs, model){


     element.parent().append(scope.data);

 }

}
});

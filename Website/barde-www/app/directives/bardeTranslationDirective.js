angular.module('app.directives', []);
angular.module('app.directives').directive('bardeTranslation', function($compile, $http, confFactory){

  return {
    restrict: 'A',
    template: '{{data}}',
    scope: {
        data: '=',
    },
    link : function(scope, element, attrs, model){

                  var data      = {'lang_code' : confFactory.LANG, content : attrs.data};
                  var headers =   {'content-type':"application/json"};


                  $http.post(confFactory.API_URL + "/lang/getTranslation", data, headers)
                  .then(function(res)
                  {
                    if (res)
                      element.parent().append(res.data.data);
                    else
                      element.parent().append(attrs.data);
                  }).catch(function (err){
                    element.parent().append(attrs.data);
                  });
                }

 }
});

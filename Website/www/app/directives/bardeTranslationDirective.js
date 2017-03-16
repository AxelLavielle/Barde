angular.module('app.directives',[]);


angular.module('app.directives').directive('bardeTranslation', function($compile, $http){


  return {
    restrict: 'A',
    template: '{{data}}',
    scope: {
        data: '=',
    },
    link : function(scope, element, attrs, model){


                  var data      = {'lang_code' : 'en-GB', content : attrs.data};
                  var headers =   {'content-type':"application/json"};


                  $http.post("http://localhost:3000/lang/translation", data, headers)
                  .then(function(res)
                  {
                    if (res)
                    {
                      element.parent().append(res.data.data);


                    }
                    else {
                      element.parent().append(attrs.data);

                    }

                  });
                }

 }
});

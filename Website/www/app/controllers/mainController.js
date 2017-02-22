angular.module('app.controllers', ['angular-md5', 'vcRecaptcha'])

        .controller('mainController', ['$scope', '$http', 'vcRecaptchaService', function($scope, $http, vcRecaptchaService)
        {

          $scope.model = {
                             key: '6LfJQBYUAAAAAPU40FqbVcOjnza1BiSrUDZJnU3W'
                         };

          $scope.contactForm = function(firstname, lastname, email, message)
          {
            if (!$scope.submitBtn)
            {
              $scope.callback = "Vous êtes un robot";

            }
          }

          $scope.setResponse = function (response) {
                        $scope.response = response;

        var data      = {'secret' : "6LfJQBYUAAAAAJIkpcszGK1vwNxXoPhbN3UGxr_O",'response' : response};
        var header =  {headers: {'Access-Control-Allow-Origin': '*'}};


          $http.post("https://www.google.com/recaptcha/api/siteverify", data)
          .then(function(res)
        {
          if (res.sucess)
          {
            $scope.submitBtn = true;
          }
          else {
            $scope.callbackClass = "red-text";
            $scope.callback = "Vous êtes un robot";
          }
        }, function (err)
      {
        $scope.callbackClass = "red-text";
        $scope.callback = "Vous êtes un robot";
      });


                    };

          $scope.newsletterForm = function (email)
          {
            var url       = "http://api.barde.io/email/"
            var data      = {'email' : email,'subscribe' : true};
            var options   =
            $http.put(url, data)

            .then(function (response) {
                    if (response.msg == "Email already exists."){
                      $scope.resClass = "red-text";
                      $scope.resValue = "Vous êtes déjà inscrit !";
                    }
                    else if (response.msg == "Email added"){
                      $scope.res_class = "green-text";
                      $scope.resValue = "Vous êtes maintenant inscrit à la newsletter";
                    }
                    else {
                      $scope.resClass = "red-text";
                      $scope.resValue = "Inscription impossible";
                    }
            }, function (err)
          {
            $scope.resClass = "red-text";
            $scope.resValue = "Inscription impossible";
          });
          }

        }]);

angular.module('app.controllers', ['angular-md5', 'vcRecaptcha'])


        .controller('mainController', ['$scope', '$http', 'vcRecaptchaService', function($scope, $http, vcRecaptchaService)
        {
          $scope.verified = false;

          $scope.model = {
            key: '6LfJQBYUAAAAAPU40FqbVcOjnza1BiSrUDZJnU3W'
          };

          $scope.contactForm = function(firstname, lastname, email, message)
          {
            if ($scope.verified)
            {

              var data      = {'name' : firstname + ' ' + lastname, 'email' : email, 'message' : message}
              var header = {headers : {'content-type':"application/json",'Access-Control-Allow-Origin' : "*"}};

              $http.post("http://api.barde.io/email/send", data, header)
              .then(function (res)
            {
              console.log(res);
            });
            }
            else {
              $scope.callbackClass = "red-text";
              $scope.callback = "Vous êtes un robot";
            }

          }

          $scope.setResponse = function (response) {
            console.log("token:" + response);
            var data      = "secret=6LfJQBYUAAAAAJIkpcszGK1vwNxXoPhbN3UGxr_O&response=" + response;
            var header = {headers : {'content-type':"application/x-www-form-urlencoded",'Access-Control-Allow-Origin' : "*"}};


            $http.post("https://www.google.com/recaptcha/api/siteverify", data, header)
            .then(function(res)
            {
              console.log(res);
              if (res.sucess)
              {
                $scope.callbackClass = "green-text";
                $scope.callback = "Vous n'êtes pas un robot";          }
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
            var data      = {'email' : email ,'subscribe' : true};
            var headers   =    {headers:{'content-type': 'application/x-www-form-urlencoded' }}

            $http.put(url, data, headers)

            .then(function (response) {
                if (response.status == 200)
                {
                  $scope.resValue = "Inscription réussie";
                  $scope.resClass = "green-text";
                }
                else if (response.status == 409) {
                  $scope.resValue = "Vous êtes déjà inscrit";
                  $scope.resClass = "red-text";
                }
                else {
                  $scope.resValue = "Une erreur est survenue";
                  $scope.resClass = "red-text";
                }
              }
              );
          }

        }]);

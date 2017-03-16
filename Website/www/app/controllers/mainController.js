angular.module('app.controllers', ['angular-md5', 'vcRecaptcha'])


        .controller('mainController', ['$scope', '$http', 'vcRecaptchaService', function($scope, $http, vcRecaptchaService)
        {

//          var userLang = navigator.language || navigator.userLanguage;
//          alert ("The language is: " + userLang);

          $scope.validated = false;

          $scope.placeholderEmail = "Email Adress";
          $scope.placeholderSend = "Send";
          $scope.placeholderMessage = "Your message";

          $scope.placeholderFirstname = "Firstname";
          $scope.placeholderLastname = "Lastname";


          $scope.setResponse = function (response) {


            var data      = {'response' : response};
            var headers =   {'content-type':"application/json"};


            $http.post("http://api.barde.io/captcha/verify", data, headers)
            .then(function(res)
            {
              if (res.data.success)
              {
                $scope.callbackClass = "green-text";
                $scope.callback = "Vous n'êtes pas un robot";
                $scope.validated = true;

              }
              else {
                $scope.callbackClass = "red-text";
            $scope.callback = "Vous êtes un robot";
              }

            });
          }


          $scope.model = {
            key: '6LfJQBYUAAAAAPU40FqbVcOjnza1BiSrUDZJnU3W'
          };

          $scope.contactForm = function(Data)
          {
            if ($scope.validated)
            {
              var data = {'name' : Data.firstname + ' ' + Data.lastname, 'email' : Data.email, 'message' : Data.message}
              var header = {headers : {'content-type':"application/json"}};

              $http.post("http://api.barde.io/email/send", data, header)
              .then(function (res)
            {
              $scope.callbackClass = "green-text";
              $scope.callback = "Le message à bien été envoyé";
              $('#newsletterModal').modal('open');


            });
            }
            else {
              $scope.callbackClass = "red-text";
              $scope.callback = "Vous êtes un robot";
            }

          }


          $scope.newsletterForm = function (email)
          {
            var url       = "http://api.barde.io/email/"
            var data      = {'email' : email ,'subscribe' : true};
            var headers   =    {headers:{'content-type': 'application/json' }}

            $http.put(url, data, headers)
            .error(function (response)
            {
                if (response.data.message)
                  Materialize.toast(response.data.message, 4000, 'top', 'center', 'red');
                else
                Materialize.toast('Une erreur est survenue', 4000, 'top', 'center', 'red');


            })
            .success(function (response) {
                Materialize.toast(response.data.message, 4000, 'top', 'center', 'green');
              }
            );
          }

        }]);

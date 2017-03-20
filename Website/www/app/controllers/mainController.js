angular.module('app.controllers')
.controller('mainController', function($scope, $http, confFactory)
{

          $scope.placeholderEmail = "Email Adress";
          $scope.placeholderSend = "Send";
          $scope.placeholderMessage = "Your message";

          $scope.placeholderFirstname = "Firstname";
          $scope.placeholderLastname = "Lastname";

          $scope.newsletterForm = function (email)
          {
            var url       = confFactory.API_URL + "/email/"
            var data      = {'email' : email ,'subscribe' : true};
            var headers   =    {headers:{'content-type': 'application/json' }}

            $http.put(url, data, headers)
            .error(function (response)
            {
                if (response.data.message)
                  Materialize.toast(response.data.message, 4000, 'top', 'center', 'red');
                else
                  Materialize.toast('An error occured', 4000, 'top', 'center', 'red');

            })
            .success(function (response) {
                Materialize.toast(response.data.message, 4000, 'top', 'center', 'green');
              }
            );
          }

        });

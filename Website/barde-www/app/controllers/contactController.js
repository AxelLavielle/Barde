angular.module('app.controllers', ['vcRecaptcha'])
.controller('contactController', ['$scope', 'vcRecaptchaService', '$http', 'confFactory', function($scope, vcRecaptchaService, $http, confFactory)
{

  $scope.validated = false;

   $scope.placeholderEmail = "Email Adress";
   $scope.placeholderSend = "Send";
   $scope.placeholderMessage = "Your message";

   $scope.placeholderFirstname = "Firstname";
   $scope.placeholderLastname = "Lastname";

   $scope.model = {
           key: confFactory.RECAPTCHA_KEY
         };


   $scope.setResponse = function (response) {


    var data      = {'response' : response};
    var headers =   {'content-type':"application/json"};


    $http.post(confFactory.API_URL + "/captcha/verify", data, headers)
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

  $scope.contactForm = function(Data)
  {
    if ($scope.validated)
    {
      var data = {'name' : Data.firstname + ' ' + Data.lastname, 'email' : Data.email, 'message' : Data.message}
      var header = {headers : {'content-type':"application/json"}};

      $http.post(confFactory.API_URL + "/email/send", data, header)
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

}]);

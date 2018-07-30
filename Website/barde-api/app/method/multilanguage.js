var Content = require('../models/lang/content');
var Lang = require('../models/lang/lang');
var Translation = require('../models/lang/translation');

exports.addContent = function (contentID, defaultValue, callback) {
  Content.findOne({content_id : contentID}, function (success, error){
    if (!success && !error)
    {
      newContent = new Content({content_id : contentID, default : defaultValue});
      newContent.save(function (error, saved){
          if (saved)
          callback(200, {
              msg: "Content added",
              data: {message: "Le contenu à bien été ajouté"}
          });
        });
    }
    else
     callback(409,{
        msg: "Content already exists",
        data: {message: "Le contenu est déjà présent"}
    });
  });
};

exports.delContent = function (contentID, callback) {
  Content.findOneAndRemove({content_id: contentID}, function (err, content) {
    if (content)
    {
      callback(200, {
        msg: "Content deleted",
        data: {message: "Le contenu à bien été supprimé"}
      });
    }
    else {
      callback(409,{
         msg: "Content doesn't exists",
         data: {message: "Le contenu n'existe pas"}
     });
    }

  });
};

exports.addTraduction = function (languageCode, contentID, value, callback) {

      Content.findOne({content_id : contentID, "content_value.lang_code" : languageCode}, function (error, success){

        if (success)
          callback(409,{msg: "Content already exists",data: {message: "Le contenu est déjà présent"}});
        else
        {
          Content.findOneAndUpdate(
            {content_id : contentID},
            {$push: {content_value: {lang_code: languageCode, content : value}}}, function (error, success){
              if (success)
                callback(200,{msg: "Content added",data: {message: "Le contenu a été ajouté"}});
              else
                callback(400,{msg: "Error",data: {message: "une erreur est survenue"}});
            });
        }
      })

};

exports.updateTraduction = function (languageCode, contentID, value, callback) {

  Content.findOneAndUpdate(
    {content_id : contentID},
    {$push: {content_value: {lang_code: languageCode, content : value}}},
    function (error, success, callback){
      callback(200, {msg: "Content added", data: {message: "Le contenu à bien modifié"}});
    });

};

exports.delTraduction = function (languageCode, contentID, callback) {
  Content.findOneAndRemove(
    {content_id : contentID, "content_value.lang_code": languageCode},
    function (error, content){
      if (content)
        callback(200, {msg: "Content deleted",data: {message: "Le contenu à bien été supprimé"}});
      else
        callback(409,{msg: "Content doesn't exists", data: {message: "Le contenu n'existe pas"}});
      });
}
exports.getTraduction = function (languageCode, contentID, callback) {


  Content.findOne({content_id : contentID}, function(error, success){
    if (error)
      callback(200, {msg: "No content", data: {message: "Le contenu n'existe pas"}});
    else if (success && success.content_value.length !== 0)
    {
       Default = success.default;
      Content.findOne({content_id : contentID},
          {
            content_value :
            {
              $elemMatch: {lang_code: languageCode}
            }
          }, function(error, success){
          if (error)
            callback(200, {msg: "No content", data: {message: "La langue n'existe pas"}});
          else if (success && success.content_value.length !== 0)
            callback(200, {data: success.content_value[0].content});
          else
          {
            callback(200, {data: Default});
          }
        });
    }
    else
      callback(200, {msg: "No content", data: {message: "Le contenu n'existe pas"}});
  });
};

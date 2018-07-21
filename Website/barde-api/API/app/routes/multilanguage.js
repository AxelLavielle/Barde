var jwt = require('jwt-simple');
var request = require("request");

var multilanguage = require('../method/multilanguage');

var Content = require('../models/lang/content');
var Lang = require('../models/lang/lang');
var Translation = require('../models/lang/translation');

module.exports = function (apiRoutes, passport) {
    apiRoutes

      .get('/lang/content', getContent)
      .put('/lang/content', addContent)

      .post('/lang/translation', getTranslation)
      .put('/lang/translation', addTranslation)

};

/**
 * @api {get} /getContent Get all traduction content
 * @apiName GetAllEmail
 * @apiGroup Lang
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "Traduction": [
 *              "content_id": "NAV_HOME_TITLE",
 *            "content_value": [
 *            {
 *              "content": "Home",
 *              "lang_code": "us",
 *              },
 *            ]
 *       }
 *     }
 */

function getContent (req, res, next)
{
  Content.find(null, function (err, response){

    if (response)
      res.status(200).send({
          msg: "Success",data: {traduction : response}
        });
    else
      res.status(400).send({
      msg: "Error",
    });
  });
}

/**
 * @api {put} /getContent Get all traduction content
 * @apiName GetAllEmail
 * @apiGroup Lang
 *
 * @apiSuccessExample 200 - Success
 *{
 * "msg": "Content added",
 * "data": {
 *    "message": "Le contenu à bien été ajouté"
 *   }
 * }
 **/


function addContent (req, res, next)
{
  if (req.body.content)
  {
    Content.findOne({content_id : req.body.content}, function (success, error){

      if (!success && !error)
      {
        newContent = new Content({content_id : req.body.content});
        newContent.save(function (ko, ok){
            if (ok)
            res.status(200).send({
                msg: "Content added",
                data: {message: "Le contenu à bien été ajouté"}
            });
          });
      }
      else
       res.status(304).send({
          msg: "Content already exists",
          data: {message: "Le contenu est déjà présent"}
      });
    });
  }
  else
   res.status(400).send({
      msg: "Bad parameters",
      data: {message: "Le contenu n'est pas valide"}
  });
}

function addTranslation (req, res, next)
{
  if (req.body.lang_code && req.body.content && req.body.value)
  {

    newTranslation = {lang_code: req.body.lang_code, content : req.body.value};

    Content.findOne(
      {content_id : req.body.content}, function(err, data) {
      if (!err && !data)
           res.status(400).send(json({success: false, msg: "no content"}));
      else
      {

      Content.findOne(
        {content_id : req.body.content, "content_value.lang_code" : req.body.lang_code},
        function (error, success){

            if (!error && !success)
            {

              Content.findOneAndUpdate(
                {content_id : req.body.content},
                {$push: {content_value: newTranslation}},
                function (error, success){
                  res.status(200).send({
                      msg: "Content added",
                      data: {message: "Le contenu à bien été ajouté"}
                  });
                });

              }
              else
              {
                 Content.update(
                   {content_id : req.body.content, "content_value.lang_code" : req.body.lang_code},
                   {$set: {"content_value.$.content": req.body.value}},
                   function (error, success){
                     res.status(200).send({
                         msg: "Content updated",
                         data: {message: "Le contenu à bien été modifié"}
                     });
                  });
              }
          });
        }
    });
  }
else
  res.status(400).send({
     msg: "Bad parameters",
     data: {message: "Le contenu n'est pas valide"}
 });
}


function getTranslation (req, res, next)
{

    if (req.body.lang_code && req.body.content)
    {
      Content.findOne({content_id : req.body.content},{content_value :
          {$elemMatch:{lang_code: req.body.lang_code}}
        }, function(error, success){
        if (error)
        res.status(200).send({
           msg: "No content",
           data: {message: "Le contenu n'existe pas"}
         });
         else if (success && success.content_value.length !== 0)
         res.status(200).send({
            data : success.content_value[0].content
          });
        else
          res.status(400).send({success: false, msg: "no content"});
      });
    }
    else
     res.status(400).send({
        msg: "Bad parameters",
        data: {message: "Le contenu n'est pas valide"}
    });
}

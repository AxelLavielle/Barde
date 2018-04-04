/**
 * Polyeezy
 * < valerian polizzi />
 * barde-api - Created on 14/03/2017
 */

/**
 * @apiDefine Translation Translation
 *
 * All routes for translation
 */

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
      .delete('/lang/content', delContent)

      .put('/lang/translation', addTranslation)
      .post('/lang/getTranslation', getTranslation)
  //    .delete('/lang/translation', delTranslation)

};


/**
 * @api {put} lang/content Get all traduction content
 * @apiName addContent
 * @apiGroup Translation
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
  if (req.body.content && req.body.default)
  {
    multilanguage.addContent(req.body.content, req.body.default, function (code, data){
      res.status(code).send(data);
    });
  }
  else
   res.status(400).send({
      msg: "Bad parameters",
      data: {message: "Missing parameters."}
  });
}

function delContent (req, res, next)
{
  if (req.body.content)
  {
    multilanguage.delContent(req.body.content, function (code, data){
      res.status(code).send(data);
    });
  }
  else
   res.status(400).send({
      msg: "Bad parameters",
      data: {message: "Missing parameters."}
  });
}


/**
 * @api {get} lang/content Get all traduction content
 * @apiName getContent
 * @apiGroup Translation
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
 * @api {put} /lang/translation add translation to a content
 * @apiName addTranslation
 * @apiGroup Translation
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
function addTranslation (req, res, next)
{
  if (req.body.lang_code && req.body.content && req.body.value)
  {
    multilanguage.addTraduction(req.body.lang_code, req.body.content, req.body.value, function (code, data){
      res.status(code).send(data);
    });
  }
else
  res.status(400).send({
     msg: "Bad parameters",
     data: {message: "Missing parameters."}
 });
}

/**
 * @api {post} /lang/getTranslation get Translated data
 * @apiName getTranslation
 * @apiGroup Translation
 *
 * @apiSuccessExample 200 - Success
 *     {
 *          "data": "EQUIPE"
 *     }
 */
function getTranslation (req, res, next)
{
    if (req.body.lang_code && req.body.content)
    {
        multilanguage.getTraduction(req.body.lang_code, req.body.content, function (code, data){
          res.status(code).send(data);
        });
    }
    else
     res.status(400).send({
        msg: "Bad parameters",
        data: {message: "Missing parameters."}
    });
}

// function delTranslation (req, res, next)
// {
//   if (req.body.lang_code && req.body.content)
//   {
//     multilanguage.delTraduction(req.body.lang_code, req.body.content, function (code, data){
//       res.status(code).send(data);
//     });
//   }
//   else
//   res.status(400).send({
//      msg: "Bad parameters",
//      data: {message: "Le contenu n'est pas valide"}
//  });
// }

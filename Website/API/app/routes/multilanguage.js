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

      .get('/lang/translation', getTranslations)
      .put('/lang/translation', addTranslation)


};

function getLanguages (req, res, next)
{
  Lang.find(null, function (err, response){
    if (err)
      return (next(err));
    res.json({data: response});
  });
}

function addLanguage (req, res, next)
{
  if (req.body.language && req.body.code)
  {
    var language = new Lang(
      {lang_name: req.body.language, lang_code : req.body.code}
    );

    language.save(function (err) {
        if (err) {
            return res.json({success: false, msg: 'Language already exists.'});
        }
        res.json({success: true, msg: 'Successful created new language.'});
    });
  }
}


function getContent (req, res, next)
{
  Content.find(null, function (err, response){
    console.log(response);

    if (err)
      return (next(err));
    res.json({data: response});
  });
}

function addContent (req, res, next)
{
  if (req.body.content)
  {
    Content.findOne({content_id : req.body.content}, function (success, error){

      if (!success && !error)
      {
        newContent = new Content({content_id : req.body.content});
        newContent.save(function (ok, ko){

        if (ko)
          return res.json({success: true, msg: req.body.content + " created"});
        return res.json({success: false, msg: req.body.content + " can't be created"});
      });

      }
      else {
        return res.json({success: true, msg: req.body.content + " already exists"});
      }
    });
  }
}

function addTranslation (req, res, next)
{
  if (req.body.lang_code && req.body.content && req.body.value)
  {
      if (req.body.lang_code)
      {
        newTranslation = new Translation({
          lang_code: req.body.lang_code, content : req.body.value
        });


        Content.findOneAndUpdate(
            { "content_id": req.body.content},
            { $set: { lang_code: req.body.lang_code }},
            {$push: {lang_code :  req.body.lang_code, content : req.body.value}},
            function(err,doc) {

                if (err) // handle error;
                  return res.json({success: false, msg: err});
                if (!doc) {
                  return res.json({success: false, msg: req.body.content + " doesn't exists"});
                }
                else {
                  console.log(doc);
                  return res.json({success: true, msg: "translation added"});
                }
            }
          );
      }
      else
        return res.json({success: false, msg: "add new language first"});
    }
}


function getTranslations (req, res, next)
{

}

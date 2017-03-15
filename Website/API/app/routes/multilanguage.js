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

    if (response)
      return res.json({success: true, data: response});
    else
    return res.json({success: false, data: []});

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
        newContent.save(function (ko, ok){
            if (ok)
              return res.json({success: true, msg: req.body.content + " created"});
            else
              return res.json({success: false, msg: req.body.content + " can't be created"});
          });
      }
      else
        return res.json({success: false, msg: req.body.content + " already exists"});
    });
  }
  else
    return res.json({success: true, msg: req.body.content + " created"});
}

function addTranslation (req, res, next)
{
  if (req.body.lang_code && req.body.content && req.body.value)
  {

    newTranslation = {lang_code: req.body.lang_code, content : req.body.value};

    Content.findOne(
      {content_id : req.body.content}, function(err, data) {
      if (!err && !data)
          return res.json({success: false, msg: "no content"});
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
                  return res.json({success: false, msg: "translation added"});
                });

              }
              else
              {
                 Content.update(
                   {content_id : req.body.content, "content_value.lang_code" : req.body.lang_code},
                   {$set: {"content_value.$.content": req.body.value}},
                   function (error, success){
                  return res.json({success: true, msg: "Value updated"});
                 });

              }
          });
      }
    });
  }
  else
    return res.json({success: false, msg: "invalid params"});

}





function getTranslation (req, res, next)
{

    if (req.body.lang_code && req.body.content)
    {
      Content.findOne(
        {content_id : req.body.content},
        {content_value : {$elemMatch: {lang_code: req.body.lang_code}}},
      function(error, success){
        console.log(success, error)
        if (error)
          return res.json({success: false, data: "value doesn't exists"});
        else if (success && success.content_value.length !== 0)
          return res.json({success: true, data: success.content_value[0].content});
        else
        return res.json({success: false, data: "value doesn't exists"});
      });
    }
    else
      return res.json({success: false, msg: "invalid params"});

}

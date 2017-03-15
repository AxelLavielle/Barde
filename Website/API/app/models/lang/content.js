/**
 * APLT
 * < arnaud perrault />
 * Created on 13/03/2017
 */

var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var translationSchema = require('./translation');
var translation = translationSchema.model('LangTranslation').schema;

var LangContent = new Schema({
    content_id : { type: String, required: true},
    data : [{
              lang_code : {type: String},
              content : {type : String}
            }]
  }
);


module.exports = mongoose.model('LangContent', LangContent);

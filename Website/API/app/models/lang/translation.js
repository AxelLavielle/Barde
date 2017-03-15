/**
 * APLT
 * < arnaud perrault />
 * API - Created on 13/03/2017
 */

var mongoose = require('mongoose');

var Schema = mongoose.Schema;
var languageSchema = require('./lang');
var language = languageSchema.model('Lang').schema;

var TranslationSchema = new Schema({
  lang_code : {type: String, index: { unique: true }},
  content : {type : String}
});

module.exports = mongoose.model('LangTranslation', TranslationSchema);

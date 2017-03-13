/**
 * APLT
 * < arnaud perrault />
 * API - Created on 13/03/2017
 */

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var TranslationSchema = new Schema({
    lang : {type : languageSchema},
    content : {type : String}
});

module.exports = mongoose.model('LangTranslation', TranslationSchema);
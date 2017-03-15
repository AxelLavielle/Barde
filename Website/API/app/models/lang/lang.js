/**
 * APLT
 * < arnaud perrault />
 * API - Created on 13/03/2017
 */

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var LangSchema = new Schema({
    lang_name : { type: String, required: true}, // FRANCAIS
    lang_code : { type: String, required: true, index: { unique: true }} // FR
});

module.exports = mongoose.model('Lang', LangSchema);

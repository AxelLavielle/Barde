/**
 * APLT
 * < arnaud perrault />
 * Created on 13/03/2017
 */

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var LangContent = new Schema({
    content_id : { type: String, required: true},
    default : { type : String},
    data : [ translationSchema ]
});

module.exports = mongoose.model('LangContent', ContentSchema);
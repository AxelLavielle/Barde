/**
 * APLT
 * < arnaud perrault />
 * barde-api - Created on 19/02/2017
 */

var mongoose = require('mongoose');
var Schema   = mongoose.Schema;
var bcrypt   = require('bcrypt');

var EmailSchema = new Schema({
    email: {
        type: String,
        unique: true,
        required: true
    },
    subscribe: {
        type: Boolean,
        required: true
    }
});

module.exports = mongoose.model('Email', EmailSchema);
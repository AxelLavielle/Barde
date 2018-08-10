/**
 * APLT
 * < arnaud perrault />
 * barde-api - Created on 19/02/2017
 */

var mongoose = require('mongoose');
var Schema   = mongoose.Schema;

var ReportSchema = new Schema({
    user: {
      type: Schema.ObjectId,
      ref: 'User',
      required: true
    },
    description: {
        type: String,
        required: true
    },
    device: {
        type: String,
        enum: ['Android', 'iOS', 'Windows'],
        required: true
    }
});

module.exports = mongoose.model('Report', ReportSchema);

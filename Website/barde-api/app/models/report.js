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

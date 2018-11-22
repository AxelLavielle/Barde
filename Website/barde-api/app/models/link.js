var mongoose = require('mongoose');
var Schema   = mongoose.Schema;

var LinkSchema = new Schema({
    link: {
      type: String,
      required: true
    },
    device: {
        type: String,
        unique: true,
        required: true
    }
});

module.exports = mongoose.model('Link', LinkSchema);

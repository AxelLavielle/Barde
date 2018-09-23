var mongoose = require('mongoose');
var Schema   = mongoose.Schema;

var PlaylistSchema = new Schema({
    name: {
      type: String,
      required: true
    },
    user: {
      type: Schema.ObjectId,
      ref: 'User',
      required: true
    },
    musics: [
      {
        id : {
          type : String,
          required: true
        },
        name: {
          type: String,
          required: true
        },
        bpm : {
          type : Number,
          required: true
        },
        seed : {
          type : Number,
          required: true
        },
        chords : [{
          type: String
        }],
        arpege : [{
          type: String
        }],
        instruments : [{
          type: String
        }]
      }
    ]
});

module.exports = mongoose.model('Playlist', PlaylistSchema);

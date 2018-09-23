/**
 * @apiDefine Playlist Playlists
 *
 * All routes for playlists
 */

var config     = require('../../config/var');
var methodAuth = require('../method/auth')();
var ObjectID = require('mongodb').ObjectID;

var Playlist = require('../models/playlist');

module.exports = function (apiRoutes, passport) {

    apiRoutes
        .get('/playlist', methodAuth.authenticate(), get)
        .get('/playlist/count', methodAuth.authenticate(), getNumber)
        .get('/playlist/:perPage/:page', methodAuth.authenticate(), getByPage)
        .post("/playlist", methodAuth.authenticate(), post)
        .put("/playlist", methodAuth.authenticate(), updatePut)
        .delete("/playlist", methodAuth.authenticate(), deletePlaylist)
        .post("/playlist/music", methodAuth.authenticate(), postMusic)
        .put("/playlist/music", methodAuth.authenticate(), updatePutMusic)
        .delete("/playlist/music", methodAuth.authenticate(), deleteMusic)
        .get('/playlist/:id', methodAuth.authenticate(), getOne)
};


/**
 * @api {get} /playlist Get all playlists
 * @apiGroup Playlist
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "playlists": []
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function get(req, res, next) {

    Playlist.find({user: req.user}).populate('user', 'email').exec(function (err, response) {

        if (err) {
            return next(err);
        }

        res.status(200).json({msg: "Success", data: {playlists: response}});
    });
}

/**
 * @api {get} /playlist/:id Get one playlist
 * @apiGroup Playlist
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "playlist": {}
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function getOne(req, res, next) {

    Playlist.findOne({"_id": req.param('id'), user: req.user}).populate('user', 'email').exec(function (err, response) {

        if (err) {
            return next(err);
        }

        res.status(200).json({msg: "Success", data: {playlist: response}});
    });
}

/**
 * @api {get} /playlist/count Get number of playlists
 * @apiGroup Playlist
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "count": Number
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function getNumber(req, res, next) {

    Playlist.count({user: req.user}, function (err, response) {

        if (err) {
            return next(err);
        }

        res.status(200).json({msg: "Success", data: {count: response}});
    });
}

/**
 * @api {get} /playlist/:perPage/:page Get playlists by page
 * @apiGroup Playlist
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "playlists": [],
 *          "page": Number,
 *          "count": Number
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function getByPage(req, res, next) {

    var perPage = Math.max(0, req.param('perPage'));
    var page    = Math.max(0, req.param('page'));


    Playlist.find({user: req.user})
        .populate('user', 'email').limit(perPage).skip(perPage * page).exec(function (err, playlists) {
        Playlist.count().exec(function (err, count) {
            res.status(200).json({msg: "Success", data: {playlists: playlists, page: page + 1, count: count / perPage}});
        })
    })
}

/**
 * @api {post} /playlist New playlist
 * @apiGroup Playlist
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "name": "",
 *     }
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Content created"
 *       "data": {
 *          "message": "Playlist saved."
 *       }
 *     }
 *
 * @apiErrorExample 400 - One param is empty
 *     {
 *       "msg": "No content"
 *       "data": {
 *          "message": param + " cannot be empty."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function post(req, res, next) {
    if (!req.body.name) {
        res.status(400).send({msg: "No content", data: {message: "Name cannot be empty."}});
    } else {
        var newPlaylist = new Playlist({
            user: req.user,
            name: req.body.name,
            musics: [],
        });

        newPlaylist.save(function (err) {
            if (err) {
              next(err);
            } else {
              res.status(200).send({
                  msg: "Content created",
                  data: {message: "Playlist saved."}
              });
            }
        });
    }

}

/**
 * @api {put} /playlist Update playlist
 * @apiGroup Playlist
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "name": "",
 *       "idPlaylist": ""
 *     }
 *
 *  @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Content updated"
 *     }
 *
 * @apiErrorExample 400 - One param is empty
 *     {
 *       "msg": "No content"
 *       "data": {
 *          "message": param + " cannot be empty."
 *       }
 *     }
 *
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item."
 *       "data": {
 *          "message": "Playlist not exists."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function updatePut(req, res, next) {
  if (!req.body.name) {
    res.status(400).send({msg: "No content", data: {message: "Name cannot be empty."}});
  } else if (!req.body.idPlaylist) {
    res.status(400).send({msg: "No content", data: {message: "IdPlaylist cannot be empty."}});
  } else {
    var updateVal = {};
    updateVal["name"] = req.body.name
    Playlist.update({
      "_id": req.body.idPlaylist, user: req.user
    }, {$set: updateVal}, function (err, response) {
      if (err) {
        return next(err);
      } else {
        if (response.n == 0) {
          res.status(404).json({msg: "Can't find item.", message: {users: "Playlist not exists."}});
        } else {
          res.status(200).send({msg: "Content updated"});
        }
      }
    });
  }
}

/**
 * @api {delete} /playlist Delete playlist
 * @apiGroup Playlist
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "idPlaylist": ""
 *     }
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "message": "Playlist deleted."
 *        }
 *     }
 *
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item"
 *       "data": {
 *          "message": "Playlist not exists."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function deletePlaylist(req, res, next) {
    Playlist.findOneAndRemove({
      "_id": req.body.idPlaylist, user: req.user
    }, function (err, response) {
      if (err)
        return next(err);
      if (!response) {
        res.status(404).send({msg: "Can't find item", data: {message: "Playlist not exists."}});
        return next(err);
      }
      res.status(200).send({msg: "Success", data: {message: "Playlist deleted."}});
    });
}

/**
 * @api {post} /playlist/music Add music to playlist
 * @apiGroup Playlist
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "idPlaylist": "",
 *       "name": "",
 *       "bpm": "",
 *       "seed": "",
 *       "chords": [],
 *       "arpege": [],
 *       "instruments": [],
 *     }
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Content created"
 *       "data": {
 *          "message": "Playlist saved."
 *       }
 *     }
 *
 * @apiErrorExample 400 - One param is empty
 *     {
 *       "msg": "No content"
 *       "data": {
 *          "message": param + " cannot be empty."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function postMusic(req, res, next) {
  if (!req.body.idPlaylist) {
      res.status(400).send({msg: "No content", data: {message: "IdPlaylist cannot be empty."}});
  } else if (!req.body.name) {
      res.status(400).send({msg: "No content", data: {message: "Name cannot be empty."}});
  } else if (!req.body.bpm) {
      res.status(400).send({msg: "No content", data: {message: "Bpm cannot be empty."}});
  } else if (!req.body.seed) {
      res.status(400).send({msg: "No content", data: {message: "Seed cannot be empty."}});
  } else if (!req.body.chords) {
      res.status(400).send({msg: "No content", data: {message: "Chords cannot be empty."}});
  } else if (!req.body.arpege) {
      res.status(400).send({msg: "No content", data: {message: "Arpege cannot be empty."}});
  } else if (!req.body.instruments) {
      res.status(400).send({msg: "No content", data: {message: "Instruments cannot be empty."}});
  } else {
    Playlist.findOne({"_id": req.body.idPlaylist, user: req.user}).exec(function (err, response) {
      if (err)
        return next(err);
      if (!response) {
        res.status(404).json({msg: "Can't find item", data: {message: "Playlist not exists."}});
        return next(err);
      }
      var music = {};
      music["name"] = req.body.name;
      music["bpm"] = req.body.bpm;
      music["seed"] = req.body.seed;
      try {
        music["chords"] = JSON.parse(req.body.chords);
        music["arpege"] = JSON.parse(req.body.arpege);
        music["instruments"] = JSON.parse(req.body.instruments);
      } catch (e) {
        return next(err);
      }
      response.musics.push(music);
      delete response._id;
      Playlist.update({"_id": req.body.idPlaylist, user: req.user}, {$set: response}, function (err, response) {
        if (err) {
          res.status(409).send({msg: "Can't update item", data: {message: "The playlist can't be update."}});
        } else {
          if (response.n == 0) {
            res.status(404).json({msg: "Can't find item.", message: {users: "Playlist not exists."}});
          } else {
            res.status(200).send({
                msg: "Content created",
                data: {message: "Playlist saved."}
            });
          }
        }
      });
    });
  }
}

/**
 * @api {put} /playlist/music Update music in playlist
 * @apiGroup Playlist
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "idPlaylist": "",
 *       "idMusic": "",
 *       "name": "",
 *       "bpm": "",
 *       "seed": "",
 *       "chords": [],
 *       "arpege": [],
 *       "instruments": [],
 *     }
 *
 *  @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Content created"
 *       "data": {
 *          "message": "Playlist saved."
 *       }
 *     }
 *
 * @apiErrorExample 400 - One param is empty
 *     {
 *       "msg": "No content"
 *       "data": {
 *          "message": param + " cannot be empty."
 *       }
 *     }
 *
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item."
 *       "data": {
 *          "message": "Playlist not exists."
 *       }
 *     }
 *
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item."
 *       "data": {
 *          "message": "Music not exists."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function updatePutMusic(req, res, next) {
  if (!req.body.idPlaylist) {
      res.status(400).send({msg: "No content", data: {message: "IdPlaylist cannot be empty."}});
  } else if (!req.body.idMusic) {
      res.status(400).send({msg: "No content", data: {message: "IdMusic cannot be empty."}});
  }else if (!req.body.name) {
      res.status(400).send({msg: "No content", data: {message: "Name cannot be empty."}});
  } else if (!req.body.bpm) {
      res.status(400).send({msg: "No content", data: {message: "Bpm cannot be empty."}});
  } else if (!req.body.seed) {
      res.status(400).send({msg: "No content", data: {message: "Seed cannot be empty."}});
  } else if (!req.body.chords) {
      res.status(400).send({msg: "No content", data: {message: "Chords cannot be empty."}});
  } else if (!req.body.arpege) {
      res.status(400).send({msg: "No content", data: {message: "Arpege cannot be empty."}});
  } else if (!req.body.instruments) {
      res.status(400).send({msg: "No content", data: {message: "Instruments cannot be empty."}});
  } else {
    Playlist.findOne({"_id": req.body.idPlaylist, user: req.user}).exec(function (err, response) {
      if (err)
        return next(err);
      if (!response) {
        res.status(404).json({msg: "Can't find item", data: {message: "Playlist not exists."}});
        return next(err);
      }
      var pos = -1;
      for (var i = 0; i < response.musics.length; i++) {
        if (response.musics[i]._id == req.body.idMusic) {
          pos = i;
          break;
        }
      }
      if (pos != -1) {
        response.musics[pos]["name"] = req.body.name;
        response.musics[pos]["bpm"] = req.body.bpm;
        response.musics[pos]["seed"] = req.body.seed;
        try {
          response.musics[pos]["chords"] = JSON.parse(req.body.chords);
          response.musics[pos]["arpege"] = JSON.parse(req.body.arpege);
          response.musics[pos]["instruments"] = JSON.parse(req.body.instruments);
        } catch (e) {
          return next(err);
        }
      } else {
        res.status(404).json({msg: "Can't find item.", message: {users: "Music not exists."}});
        return next(err);
      }
      delete response._id;
      Playlist.update({"_id": req.body.idPlaylist, user: req.user}, {$set: response}, function (err, response) {
        if (err) {
          res.status(409).send({msg: "Can't update item", data: {message: "The playlist can't be update."}});
        } else {
          if (response.n == 0) {
            res.status(404).json({msg: "Can't find item.", message: {users: "Playlist not exists."}});
          } else {
            res.status(200).send({
                msg: "Content created",
                data: {message: "Playlist saved."}
            });
          }
        }
      });
    });
  }
}


/**
 * @api {delete} /playlist/music Delete music in playlist
 * @apiGroup Playlist
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "idPlaylist": ""
 *       "idMusic": ""
 *     }
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "message": "Music deleted."
*        }
 *     }
 *
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item"
 *       "data": {
 *          "message": "Playlist not exists."
 *       }
 *     }
 *
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item"
 *       "data": {
 *          "message": "Music not exists."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function deleteMusic(req, res, next) {
    Playlist.findOne({"_id": req.body.idPlaylist, user: req.user}).exec(function (err, response) {
      if (err)
        return next(err);
      if (!response) {
        res.status(404).json({msg: "Can't find item", data: {message: "Playlist not exists."}});
        return next(err);
      }
      var pos = -1;
      for (var i = 0; i < response.musics.length; i++) {
        if (response.musics[i]._id == req.body.idMusic) {
          pos = i;
          break;
        }
      }
      if (pos != -1) {
        response.musics.splice(pos, 1);
      } else {
        res.status(404).json({msg: "Can't find item.", message: {users: "Music not exists."}});
        return next(err);
      }
      delete response._id;
      Playlist.update({"_id": req.body.idPlaylist, user: req.user}, {$set: response}, function (err, response) {
        if (err) {
          res.status(409).send({msg: "Can't update item", data: {message: "The playlist can't be update."}});
        } else {
          if (response.n == 0) {
            res.status(404).json({msg: "Can't find item.", message: {users: "Playlist not exists."}});
          } else {
            res.status(200).send({msg: "Content updated"});
          }
        }
      });
    });
}

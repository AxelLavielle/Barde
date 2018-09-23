/**
 * @Author: Alexis Miele
 * @Date:   2018-01-16T19:01:20+01:00
 * @Email:  alexis.miele@epitech.eu
 * @Last modified by:   Alexis Miele
 * @Last modified time: 2018-01-17T14:49:45+01:00
 */



/**
 * APLT
 * < arnaud perrault />
 * API - Created on 21/03/2017
 */

/**
 * @apiDefine User Users
 *
 * All routes for users
 */

var config     = require('../../config/var');
var methodAuth = require('../method/auth')();
var mailer  = require("../method/email");
var crypto = require("crypto");

var User = require('../models/user');

module.exports = function (apiRoutes, passport) {

    apiRoutes
        .get('/user', methodAuth.authenticate(), methodAuth.admin(), get)
        .get('/user/me', methodAuth.authenticate(), getMe)
        .get('/user/count', methodAuth.authenticate(), methodAuth.admin(), getNumber)
        .delete("/user", methodAuth.authenticate(), methodAuth.admin(), del)
        .patch("/user", methodAuth.authenticate(), updatePatch)
        .put("/user", methodAuth.authenticate(), updatePut)
        .put("/user/password", methodAuth.authenticate(), password)
        .get("/user/password/reset", methodAuth.authenticate(), passwordResetGet)
        .post("/user/password/reset", methodAuth.authenticate(), passwordResetPost)
        .get('/user/:email', methodAuth.authenticate(), methodAuth.admin(), getOne)
        .get('/user/:perPage/:page', methodAuth.authenticate(), methodAuth.admin(), getByPage)};


/**
 * @api {get} /user Get all users
 * @apiGroup User
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "users": []
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

    User.find(null, function (err, response) {

        if (err) {
            return next(err);
        }

        res.status(200).json({msg: "Success", data: {users: response}});
    });
}

/**
 * @api {get} /user/me Get user authenticated
 * @apiGroup User
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "user": []
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function getMe(req, res, next) {

    // User.find(null, function (err, response) {
    //
    //     if (err) {
    //         return next(err);
    //     }
    //
    // });
    delete req.user._id;
    if (req.user.reset) {
      delete req.user.reset
    }
    res.status(200).json({msg: "Success", data: {user: req.user}});
}

/**
 * @api {get} /user/count Get number of users
 * @apiGroup User
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

    User.count(null, function (err, response) {

        if (err) {
            return next(err);
        }

        res.status(200).json({msg: "Success", data: {count: response}});
    });
}

/**
 * @api {get} /user/:perPage/:page Get users by page
 * @apiGroup User
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "users": [],
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


    User.find()
        .limit(perPage).skip(perPage * page).sort({email: "asc"}).exec(function (err, users) {
        User.count().exec(function (err, count) {
            res.status(200).json({msg: "Success", data: {users: users, page: page + 1, count: count / perPage}});
        })
    })
}

/**
 * @api {get} /user/:email Get one users
 * @apiGroup User
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "user": {}
 *       }
 *     }
 *
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item."
 *       "data": {
 *          "message": "User not exists."
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

    User.findOne({
        email: req.params.email.toLowerCase()
    }, function (err, response) {

        if (err) {
            return next(err);
        }

        if (!response) {
            res.status(404).json({msg: "Can't find item.", message: {users: "User not exists."}});
            return next(err);
        }

        res.status(200).json({msg: "Success", data: {user: response}});
    });

}


/**
 * @api {patch} /user/ Update user (Partially)
 * @apiGroup User
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "email": "",
 *       "userNAme": "",
 *       "password": "",
 *       "firstName": "",
 *       "lastName": "",
 *       "yearOfBirth": "",
 *       "monthOfBirth": "",
 *       "dayOfBirth": "",
 *       "role": ""
 *     }
 *
 *  @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Content updated"
 *     }
 *
 * @apiErrorExample 400 - Email is empty
 *     {
 *       "msg": "No content"
 *       "data": {
 *          "message": "Email cannot be empty."
 *       }
 *     }
 *
 *  @apiErrorExample 409 - User already exists
 *     {
 *       "msg": "Content already exists"
 *       "data": {
 *          "message": "The username you have used is already registered."
 *       }
 *     }
 *
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item."
 *       "data": {
 *          "message": "User not exists."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function updatePatch(req, res, next) {
  if (!req.body.email) {
    res.status(400).send({msg: "No content", data: {message: "Email cannot be empty."}});
  } else if (req.body.email === req.user.email || req.user.role === "Admin") {
    var updateVal = {}
    if (req.body.role && req.user.role === "Admin") {
      updateVal["role"] = req.body.role
    }
    if (req.body.userName) {
      updateVal["name.userName"] = req.body.userName
    }
    if (req.body.firstName) {
      updateVal["name.firstName"] = req.body.firstName
    }
    if (req.body.lastName) {
      updateVal["name.lastName"] = req.body.lastName
    }
    if (req.body.yearOfBirth && req.body.monthOfBirth && req.body.dayOfBirth) {
      updateVal["dateOfBirth"] = new Date(req.body.yearOfBirth, req.body.monthOfBirth, req.body.dayOfBirth)
    }
    User.update({email: req.body.email.toLowerCase()}, {$set: updateVal}, function (err, response) {
      if (err) {
        res.status(409).send({msg: "Content already exists", data: {message: "The username you have used is already registered."}});
      } else {
        if (response.n == 0) {
          res.status(404).json({msg: "Can't find item.", message: {users: "User not exists."}});
        } else {
          res.status(200).send({msg: "Content updated"});
        }
      }
    });
  } else {
    res.status(401).send('Unauthorized');
  }
}


/**
 * @api {put} /user/ Update user (Fully)
 * @apiGroup User
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "email": "",
 *       "userName": "",
 *       "password": "",
 *       "firstName": "",
 *       "lastName": "",
 *       "yearOfBirth": "",
 *       "monthOfBirth": "",
 *       "dayOfBirth": "",
 *       "role": ""
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
 *  @apiErrorExample 409 - User already exists
 *     {
 *       "msg": "Content already exists"
 *       "data": {
 *          "message": "The username you have used is already registered."
 *       }
 *     }
 *
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item."
 *       "data": {
 *          "message": "User not exists."
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
  if (!req.body.email) {
    res.status(400).send({msg: "No content", data: {message: "Email cannot be empty."}});
  } else if (!req.body.userName) {
    res.status(400).send({msg: "No content", data: {message: "UserName cannot be empty."}});
  } else if (!req.body.firstName || !req.body.lastName) {
    res.status(400).send({msg: "No content", data: {message: "FirstName and/or lastName cannot be empty."}});
  } else if (!req.body.yearOfBirth || !req.body.monthOfBirth || !req.body.dayOfBirth) {
    res.status(400).send({msg: "No content", data: {message: "DateOfBirth cannot be empty."}});
  } else if (req.body.email === req.user.email || req.user.role === "Admin") {
    var updateVal = {
        dateOfBirth: new Date(req.body.yearOfBirth, req.body.monthOfBirth, req.body.dayOfBirth),
    }
    updateVal["name.userName"] = req.body.userName
    updateVal["name.firstName"] = req.body.firstName
    updateVal["name.lastName"] = req.body.lastName
    if (req.body.role && req.user.role === "Admin") {
      updateVal["role"] = req.body.role
    }
    User.update({email: req.body.email.toLowerCase()}, {$set: updateVal}, function (err, response) {
      if (err) {
        res.status(409).send({msg: "Content already exists", data: {message: "The username you have used is already registered."}});
      } else {
        if (response.n == 0) {
          res.status(404).json({msg: "Can't find item.", message: {users: "User not exists."}});
        } else {
          res.status(200).send({msg: "Content updated"});
        }
      }
    });
  } else {
    res.status(401).send('Unauthorized');
  }
}


/**
 * @api {delete} /user/ Delete user
 * @apiName DeleteUser
 * @apiGroup User
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "email": ""
 *     }
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "message": "User deleted."
*        }
 *     }
 *
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item"
 *       "data": {
 *          "message": "User not exists."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function del(req, res, next) {
    User.findOneAndRemove({
      "email": req.body.email.toLowerCase()
    }, function (err, response) {
      if (err)
        return next(err);
      if (!response) {
        res.status(404).json({msg: "Can't find item", data: {message: "User not exists."}});
        return next(err);
      }
      res.status(200).send({msg: "Success", data: {message: "User deleted."}});
    });

}


/**
 * @api {put} /user/password Update user's password
 * @apiGroup User
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "email": "",
 *       "password": "",
 *       "newPassword": ""
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
 *          "message": "User not exists."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Wrong password
 *     {
 *       "msg": "Unauthorized"
 *       "data": {
 *          "message": "Wrong password."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function password(req, res, next) {
  if (!req.body.email) {
    res.status(400).send({msg: "No content", data: {message: "Email cannot be empty."}});
  } else if (!req.body.password || (req.body.email != req.user.email && req.user.role === "Admin")) {
    res.status(400).send({msg: "No content", data: {message: "Password cannot be empty."}});
  } else if (!req.body.newPassword) {
    res.status(400).send({msg: "No content", data: {message: "NewPassword cannot be empty."}});
  } else if (req.body.email === req.user.email || req.user.role === "Admin") {
    var updateVal = {
        password: req.body.newPassword,
    }
    User.findOne({
        email: req.body.email.toLowerCase()
    }, function (err, response) {
        if (err) {
            return next(err);
        }
        if (!response) {
            res.status(404).json({msg: "Can't find item.", message: {users: "User not exists."}});
            return next(err);
        }
        if (req.body.email != req.user.email && req.user.role === "Admin") {
          User.update({email: req.body.email.toLowerCase()}, {$set: updateVal}, function (err, response) {
            if (err) {
              return next(err);
            } else {
              if (response.n == 0) {
                res.status(404).json({msg: "Can't find item.", message: {users: "User not exists."}});
              } else {
                res.status(200).send({msg: "Content updated"});
              }
            }
          });
        } else {
          response.comparePassword(req.body.password, function (err, isMatch) {
              if (isMatch && !err) {
                User.update({email: req.body.email.toLowerCase()}, {$set: updateVal}, function (err, response) {
                  if (err) {
                    return next(err);
                  } else {
                    if (response.n == 0) {
                      res.status(404).json({msg: "Can't find item.", message: {users: "User not exists."}});
                    } else {
                      res.status(200).send({msg: "Content updated"});
                    }
                  }
                });
              } else {
                  res.status(401).send({
                      msg: "Unauthorized",
                      data: {message: "Wrong password."}
                  });
              }
          });
        }
    });
  } else {
    res.status(401).send('Unauthorized');
  }
}

/**
 * @api {get} /user/password/reset Ask password reset
 * @apiGroup User
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *     }
 *
 *  @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "message": "Email sent."
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
 * @apiErrorExample 400 - Email error
 *     {
 *       "msg": "Error"
 *       "data": {
 *          "message": "Email error."
 *       }
 *     }
 *
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item."
 *       "data": {
 *          "message": "User not exists."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Wait 2hour
 *     {
 *       "msg": "Wait"
 *       "data": {
 *          "message": "You need to wait before send a new email."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function passwordResetGet(req, res, next) {
  User.findOne({
      email: req.user.email
  }, function (err, response) {
      if (err) {
          return next(err);
      }
      if (!response) {
          res.status(404).send({msg: "Can't find item.", message: {users: "User not exists."}});
          return next(err);
      }
      if (response.reset && response.reset.date) {
        var now = new Date();
        if ((now - response.reset.date) / (1000 * 60 * 60) >= 2) {
          res.status(401).send({msg: "Wait", data: {message: "You need to wait before send a new email."}});
          return ;
        }
      }
      var token = crypto.randomBytes(3*4).toString('base64');
      var updateVal = {
        reset: {
          date: new Date(),
          token: token,
          used: false
        }
      }
      User.update({email: req.user.email}, {$set: updateVal}, function (err, response) {
        if (err) {
          return next(err);
        } else {
          if (response.n == 0) {
            res.status(404).send({msg: "Can't find item.", message: {users: "User not exists."}});
          } else {
            mailer.sendEmailResetPassword("Barde.io", "noreply@barde.io", req.user.email, "This is your token available 2hours to reset your password: " + token, function (rtn) {
                if (rtn.success)
                    res.status(200).send({msg: "Success", data: {message: "Email sent."}});
                else
                    res.status(400).send({msg: "Error", data: {message: "Email error."}});

            });
          }
        }
      });
  });
}

/**
 * @api {post} /user/password/reset Reset password
 * @apiGroup User
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "token": "",
 *       "password": "",
 *     }
 *
 *  @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "message": "Email sent."
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
 * @apiErrorExample 400 - No token
 *     {
 *       "msg": "Error"
 *       "data": {
 *          "message": "You need to ask for a token."
 *       }
 *     }
 *
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item."
 *       "data": {
 *          "message": "User not exists."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Expired or already used
 *     {
 *       "msg": "Error"
 *       "data": {
 *          "message": "Token expired or already used."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function passwordResetPost(req, res, next) {
  if (!req.body.token) {
    res.status(400).send({msg: "No content", data: {message: "Token cannot be empty."}});
  } else if (!req.body.password) {
    res.status(400).send({msg: "No content", data: {message: "Password cannot be empty."}});
  } else {
    User.findOne({
        email: req.user.email
    }, function (err, response) {
        if (err) {
            return next(err);
        }
        if (!response) {
            res.status(404).json({msg: "Can't find item.", message: {users: "User not exists."}});
            return next(err);
        }
        if (response.reset && response.reset.date && response.reset.token) {
          var now = new Date();
          if ((now - response.reset.date) / (1000 * 60 * 60) > 2 || response.reset.used || req.body.token != response.reset.token) {
            res.status(401).send({msg: "Error", data: {message: "Token expired or already used."}});
            return next(err);
          }
          var updateVal = {
              password: req.body.password,
              reset: {
                used: true
              }
          }
          User.update({email: req.user.email}, {$set: updateVal}, function (err, response) {
            if (err) {
              return next(err);
            } else {
              if (response.n == 0) {
                res.status(404).json({msg: "Can't find item.", message: {users: "User not exists."}});
              } else {
                res.status(200).send({msg: "Content updated"});
              }
            }
          });
        } else {
          res.status(400).send({msg: "Error", data: {message: "You need to ask for a token."}});
        }
      });
    }
}

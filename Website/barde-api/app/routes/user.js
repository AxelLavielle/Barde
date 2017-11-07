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

var User = require('../models/user');

module.exports = function (apiRoutes, passport) {

    apiRoutes
        .get('/user', get)
        .get('/user/count', getNumber)
        .get('/user/:email', getOne)
        .get('/user/:perPage/:page', getByPage)
        .delete("/user", methodAuth.authenticate(), methodAuth.admin(), del)
        .patch("/user", methodAuth.authenticate(), updatePatch)
        .put("/user", methodAuth.authenticate(), updatePut)
};


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
 */
function getByPage(req, res, next) {

    var perPage = Math.max(0, req.param('perPage'));
    var page    = Math.max(0, req.param('page'));

    console.log(typeof(perPage), typeof(page))

    User.find()
        .limit(perPage).skip(perPage * page).sort({email: "asc"}).exec(function (err, users) {
        console.log(users);
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
 */
function getOne(req, res, next) {

    User.findOne({
        email: req.params.email
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
 * @api {patch} /user/ Update user
 * @apiGroup User
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "email": ""
 *     }
 *
 *  @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Content updated"
 *     }
 */
function updatePatch(req, res, next) {

    if (!req.body.email) {
      res.status(400).send({msg: "No content", data: {message: "Email cannot be empty."}});
    } else if (req.body.email === req.user.email || req.user.role === "Admin") {
      var updateVal = {}
      if (req.body.role && req.user.role === "Admin") {
        updateVal["role"] = req.body.role
      }
      if (req.body.password) {
        updateVal["password"] = req.body.password
      }
      if (req.body.firstName) {
        if (!updateVal["name"]) {
          updateVal["name"] = {}
        }
        updateVal["name"]["firstName"] = req.body.firstName
      }
      if (req.body.lastName) {
        if (!updateVal["name"]) {
          updateVal["name"] = {}
        }
        updateVal["name"]["lastName"] = req.body.lastName
      }
      if (req.body.yearOfBirth && req.body.monthOfBirth && req.body.dayOfBirth) {
        updateVal["dateOfBirth"] = new Date(req.body.yearOfBirth, req.body.monthOfBirth, req.body.dayOfBirth)
      }
      User.update({email: req.body.email}, {$set: updateVal}, function (err, response) {
          if (err)
              return next(err);
          res.status(200).send({msg: "Content updated"});
      });
    } else {
      res.status(401).send('Unauthorized');
    }
}


/**
 * @api {put} /user/ Update user
 * @apiGroup User
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "email": ""
 *     }
 *
 *  @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Content updated"
 *     }
 */
function updatePut(req, res, next) {

    if (!req.body.email) {
      res.status(400).send({msg: "No content", data: {message: "Email cannot be empty."}});
    } else if (!req.body.firstName || !req.body.lastName) {
      res.status(400).send({msg: "No content", data: {message: "FirstName and/or lastName cannot be empty."}});
    } else if (!req.body.yearOfBirth || !req.body.monthOfBirth || !req.body.dayOfBirth) {
      res.status(400).send({msg: "No content", data: {message: "DateOfBirth cannot be empty."}});
    } else if (req.body.email === req.user.email || req.user.role === "Admin") {
      var updateVal = {
          name: {
            firstName: req.body.firstName,
            lastName: req.body.lastName,
          },
          dateOfBirth: new Date(req.body.yearOfBirth, req.body.monthOfBirth, req.body.dayOfBirth),
      }
      if (req.body.password) {
        updateVal["password"] = req.body.password
      }
      if (req.body.role && req.user.role === "Admin") {
        updateVal["role"] = req.body.role
      }
      User.update({email: req.body.email}, {$set: updateVal}, function (err, response) {
          if (err)
              return next(err);
          res.status(200).send({msg: "Content updated"});
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
 */
function del(req, res, next) {
    User.findOneAndRemove({
      "email": req.body.email
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

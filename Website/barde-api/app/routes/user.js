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
        .get('/user/:email', getOne)
        .delete("/user", del)
        .patch("/user", methodAuth.authenticate(), methodAuth.admin(), update)
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
function update(req, res, next) {

    console.log(req.user);

    Email.update({"email": req.body.email}, function (err, response) {
        if (err)
            return next(err);
        res.status(200).send({msg: "Content updated"});
    });

}


/**
 * @api {delete} /email/ Delete email
 * @apiName DeleteEmail
 * @apiGroup Email
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "email": ""
 *     }
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Content deleted"
 *     }
 */
function del(req, res, next) {
    Email.delete({"email": req.body.email}, function (err, response) {
        if (err)
            return next(err);
        res.status(200).send({msg: "Content deleted"});
    });

}
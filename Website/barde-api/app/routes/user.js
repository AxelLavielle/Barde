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

    User.find().select('email')
        .limit(perPage).skip(perPage * page).sort({email: "asc"}).exec(function (err, users) {
        console.log(users);
        User.count().exec(function (err, count) {
            res.status(200).json({msg: "Success", data: {users: users, page: page, count: count / perPage}});
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
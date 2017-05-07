/**
 * APLT
 * < arnaud perrault />
 * barde-api - Created on 14/03/2017
 */

var jwt        = require('jwt-simple');
var config     = require('../../config/var');
var User       = require('../models/user');
var methodAuth = require('../method/auth')();

module.exports = function (apiRoutes, passport) {

    apiRoutes
        .post('/auth/register', register)
        .post('/auth/login', login)
        .get('/info', methodAuth.authenticate(), methodAuth.admin(), info)
        .get('/auth/isAuthenticate', isAuthenticate)
        .get('/auth/isAdmin', methodAuth.authenticate(), isAdmin)

};

/**
 * @api {post} /auth/register Register user
 * @apiName Login
 * @apiGroup Auth
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "email": "",
 *       "password": ""
 *     }
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Content created"
 *       "data": {
 *          "message": "You are now registered."
 *       }
 *     }
 *
 * @apiErrorExample 400 - No email
 *     {
 *       "msg": "No content"
 *       "data": {
 *          "message": "Email cannot be empty."
 *       }
 *     }
 *
 * @apiErrorExample 400 - No password
 *     {
 *       "msg": "Wrong content"
 *       "data": {
 *          "message": "Password cannot be empty."
 *       }
 *     }
 *
 *  @apiErrorExample 409 - User already exists
 *     {
 *       "msg": "Content already exists"
 *       "data": {
 *          "message": "The email address you have used is already registered."
 *       }
 *     }
 */
function register(req, res, next) {

    console.log(req.body);

    if (!req.body.email) {
        res.status(400).send({msg: "No content", data: {message: "Vous devez inscrire votre email."}});
    } else if (!req.body.email) {
        res.status(400).send({msg: "No content", data: {message: "Vous devez inscrire votre mot de passe."}});
    } else {
        var newUser = new User({
            email: req.body.email,
            password: req.body.password
        });

        newUser.save(function (err) {
            console.log(err);
            if (err) {
                res.status(409).send({msg: "Content already exists", data: {message: "L'utilisateur existe déjà."}});
            }
            res.status(200).send({
                msg: "Content created",
                data: {message: "Votre inscription a bien été pris en compte."}
            });
        });
    }

}

/**
 * @api {post} /auth/login Login user
 * @apiName Login
 * @apiGroup Auth
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "email": "",
 *       "password": ""
 *     }
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Content created"
 *       "data": {
 *          "token": "JWT " + token
 *          "message": "You are connected."
 *       }
 *     }
 *
 * @apiErrorExample 400 - User not exist
 *     {
 *       "msg": "No content"
 *       "data": {
 *          "message": "The email or password is incorrect."
 *       }
 *     }
 *
 * @apiErrorExample 400 - Wrong content
 *     {
 *       "msg": "Wrong content"
 *       "data": {
 *          "message": "The email or password is incorrect."
 *       }
 *     }
 */
function login(req, res, next) {

    console.log(req.body);

    User.findOne({
        email: req.body.email
    }, function (err, user) {
        if (err) throw err;

        if (!user) {
            res.status(400).send({msg: "No content", data: {message: "The email or password is incorrect."}});
        } else {
            // check if password matches
            user.comparePassword(req.body.password, function (err, isMatch) {
                if (isMatch && !err) {
                    // if user is found and password is right create a token
                    var token = jwt.encode(user, config.jwt.secret);

                    res.status(200).send({
                        msg: "Content created",
                        data: {token: "JWT " + token, message: "You are connected."}
                    });


                } else {
                    res.status(400).send({
                        msg: "Wrong content",
                        data: {message: "The email or password is incorrect."}
                    });
                }
            });
        }
    });

}

/**
 * @api {get} /auth/isAdmin Check if user is Admin
 * @apiName isAdmin
 * @apiGroup Auth
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "isAdmin": true
 *       }
 *     }
 *
 * @apiErrorExample 403 - Forbidden
 *     {
 *       "msg": "Forbidden"
 *       "data": {
 *          "isAdmin": false
 *       }
 *     }
 *
 */
function isAdmin(req, res, next) {
    if (req.user.role === "Admin")
        res.status(200).send({msg: "Success", data: {"isAdmin": true}});
    else
        res.status(403).send({msg: "Error", data: {"isAdmin": false}})
}

/**
 * @api {get} /auth/isAuthenticate Check if user is authenticate
 * @apiName isAuthenticate
 * @apiGroup Auth
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "isAuthenticate": true
 *       }
 *     }
 *
 * @apiErrorExample 403 - Forbidden
 *     {
 *       "msg": "Forbidden"
 *       "data": {
 *          "isAuthenticate": false
 *       }
 *     }
 *
 */
function isAuthenticate(req, res, next) {
    if (req.user.role === "Admin" || req.user.role === "Client")
        res.status(200).send({msg: "Success", data: {"isAuthenticate": true}});
    else
        res.status(403).send({msg: "Error", data: {"isAuthenticate": false}})
}

/**
 * @api {get} /info Example route
 * @apiName Example
 * @apiGroup Auth
 *
 */
function info(req, res, next) {
    /*
     res.send(req.isAuthenticated() ? req.user : '0');
     */
    res.status(200).send({"msg": "ok"})
}
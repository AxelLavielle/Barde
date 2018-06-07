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
        .get('/auth/isAuthenticate', methodAuth.isAuthenticate(), isAuthenticate)
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
 *       "password": "",
 *       "firstName": "",
 *       "lastName": "",
 *       "userName": "",
 *       "yearOfBirth": "",
 *       "monthOfBirth": "",
 *       "dayOfBirth": "",
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
 *          "message": "The email address or the username you have used is already registered."
 *       }
 *     }
 *
 *  @apiErrorExample 400 - Email validation failed
 *     {
 *       "msg": "Content validation"
 *       "data": {
 *          "message": "The email format is wrong."
 *       }
 *     }
 *
 *  @apiErrorExample 400 - DateOfBirth validation failed
 *     {
 *       "msg": "Content validation"
 *       "data": {
 *          "message": "The date of birth is wrong."
 *       }
 *     }
 */
function register(req, res, next) {
    if (!req.body.email) {
        res.status(400).send({msg: "No content", data: {message: "Email cannot be empty."}});
    } else if (!req.body.password) {
        res.status(400).send({msg: "No content", data: {message: "Password cannot be empty."}});
    } else if (!req.body.userName) {
        res.status(400).send({msg: "No content", data: {message: "UserName cannot be empty."}});
    } else if (!req.body.firstName || !req.body.lastName) {
        res.status(400).send({msg: "No content", data: {message: "FirstName and/or lastName cannot be empty."}});
    } else if (!req.body.yearOfBirth || !req.body.monthOfBirth || !req.body.dayOfBirth) {
        res.status(400).send({msg: "No content", data: {message: "DateOfBirth cannot be empty."}});
    } else {
        var newUser = new User({
            email: req.body.email,
            password: req.body.password,
            name: {
              firstName: req.body.firstName,
              lastName: req.body.lastName,
              userName: req.body.userName,
            },
            dateOfBirth: new Date(req.body.yearOfBirth, req.body.monthOfBirth, req.body.dayOfBirth),
        });

        newUser.policyPassword(function (error) {
          if (!error) {
            newUser.save(function (err) {
                if (err) {
                    if (err.errors && err.errors.email)
                      res.status(400).send({msg: "Content validation", data: {message: err.errors.email.message}});
                    else if (err.errors && err.errors.dateOfBirth)
                      res.status(400).send({msg: "Content validation", data: {message: err.errors.dateOfBirth.message}});
                    else
                      res.status(409).send({msg: "Content already exists", data: {message: "The email address or the username you have used is already registered."}});
                } else {
                  res.status(200).send({
                      msg: "Content created",
                      data: {message: "You are now registered."}
                  });
                }
            });
          } else {
            res.status(400).send({msg: error.name, data: {message: error.message}});
          }
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
    User.findOne({
        email: req.body.email.toLowerCase()
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
    if (req.user && (req.user.role === "Admin" || req.user.role === "Client"))
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

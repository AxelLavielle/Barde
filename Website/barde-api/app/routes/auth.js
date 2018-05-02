/**
 * APLT
 * < arnaud perrault />
 * barde-api - Created on 14/03/2017
 */

var jwt    = require('jwt-simple');
var User   = require('../models/user');
var config = require('../../config/var');
var bcrypt = require('bcrypt');

module.exports = function (apiRoutes, passport) {

    apiRoutes
        .post('/register', register)
        .post('/login', login)

};


/**
 * @api {post} /auth/register Register user
 * @apiName Login
 * @apiGroup Auth
 *
<<<<<<< HEAD
 *
 * @apiErrorExample 200 - Success
=======
 * @apiParamExample {json} Request-Example:
 *     {
 *       "email": "",
 *       "password": ""
 *     }
 *
 * @apiSuccessExample 200 - Success
>>>>>>> 8decf7db36143b67de99eaa9d97006f88d870cd8
 *     {
 *       "msg": "Content created"
 *       "data": {
 *          "message": "Votre inscription a bien été pris en compte."
 *       }
 *     }
 *
 * @apiErrorExample 400 - No email
 *     {
 *       "msg": "No content"
 *       "data": {
 *          "message": "Vous devez inscrire votre email."
 *       }
 *     }
 *
 * @apiErrorExample 400 - No password
 *     {
 *       "msg": "Wrong content"
 *       "data": {
 *          "message": "Vous devez inscrire votre mot de passe."
 *       }
 *     }
 *
 *  @apiErrorExample 409 - User already exists
 *     {
 *       "msg": "Content already exists"
 *       "data": {
 *          "message": "L'utilisateur existe déjà."
 *       }
 *     }
 */
function register(req, res, next) {

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
 *          "message": "Vous êtes connecté."
 *       }
 *     }
 *
 * @apiErrorExample 400 - User not exist
 *     {
 *       "msg": "No content"
 *       "data": {
 *          "message": "L'utilisateur n'existe pas."
 *       }
 *     }
 *
 * @apiErrorExample 400 - Wrong content
 *     {
 *       "msg": "Wrong content"
 *       "data": {
 *          "message": "Le mot de passe est faux."
 *       }
 *     }
 */
function login(req, res, next) {

    User.findOne({
        email: req.body.email
    }, function (err, user) {
        if (err) throw err;

        if (!user) {
            res.status(400).send({msg: "No content", data: {message: "L'utilisateur n'existe pas."}});
        } else {
            // check if password matches
            user.comparePassword(req.body.password, function (err, isMatch) {
                if (isMatch && !err) {
                    // if user is found and password is right create a token
                    var token = jwt.encode(user, config.jwt.secret);
                    // return the information including token as JSON
                    res.json({success: true, token: "JWT " + token});

                    res.status(200).send({
                        msg: "Content created",
                        data: {token: "JWT " + token, message: "Vous êtes connecté."}
                    });


                } else {
                    res.status(400).send({msg: "Wrong content", data: {message: "Le mot de passe est faux."}});
                }
            });
        }
    });

}

var jwt = require('jwt-simple');
var User = require('../models/user');
var config = require('../../config/db'); // get db config file
var popupTools = require('popup-tools');
var bcrypt = require('bcrypt');

module.exports = function (apiRoutes, passport) {

    apiRoutes
        .post('/signup', signup)
        .post('/authenticate', authenticate)

        .get('/auth/facebook/callback', passport.authenticate('facebook'), facebookCallback)
        .get('/auth/facebook', passport.authenticate('facebook', {scope: ['email']}))

        .get('/auth/local/callback', passport.authenticate('facebook'), facebookCallback)
        .get('/auth/local', passport.authenticate('local', {failureRedirect: '/signup'}), localRegister)


};

function localRegister(req, res)
{
    res.redirect('/');
}

function facebookCallback(req, res) {
    res.end(popupTools.popupResponse(req.user))
}

function signup(req, res, next) {
    console.log(req.body);

    var password = ((req.body.social.facebook.id != "" || req.body.social.twitter.id != "") ? "*" : req.body.password);
    var facebookId = (req.body.social.facebook.id == "" ? "" : req.body.social.facebook.id);
    var twitterId = (req.body.social.twitter.id == "" ? "" : req.body.social.twitter.id);

    if (!req.body.email) {
        res.json({success: false, msg: 'Please enter email and password.'});
    } else {
        var newUser = new User({
            email: req.body.email,
            name: {
                lastName: req.body.name.lastName,
                firstName: req.body.name.firstName,
                userName: req.body.name.userName
            },
            password: password,
            social: {
                facebook: {
                    id: facebookId
                },
                twitter: {
                    id: twitterId,
                }
            }
        });
        console.log("=", newUser);
        // save the user
        newUser.save(function (err) {
            console.log(err);
            if (err) {
                return res.json({success: false, msg: 'Username already exists.'});
            }
            res.json({success: true, msg: 'Successful created new user.'});
        });
    }
}

function authenticate(req, res, next) {


    console.log(req.body);

    if (req.body.social && ((req.body.social.facebook && req.body.social.facebook.id != "") || (req.body.social.twitter && req.body.social.twitter.id != ""))) {
        User.findOne({
            'social.facebook.id': req.body.social.facebook.id
        }, function (err, user) {

            if (err) throw err;

            if (!user) {
                res.send({success: false, msg: 'Authentication failed. User not found.'});
            } else {
                if (req.body.social.facebook.id == user.social.facebook.id || req.body.social.twitter.id == user.social.twitter.id) {

                    var token = jwt.encode(user, config.secret);

                    // return the information including token as JSON
                    res.json({success: true, token: 'JWT ' + token});
                }
                else {
                    res.send({success: false, msg: 'Authentication failed. Wrong password.'});
                }

            }
        });
    }
    else {
        User.findOne({
            email: req.body.email
        }, function (err, user) {
            if (err) throw err;

            if (!user) {
                res.send({success: false, msg: 'Authentication failed. User not found.'});
            } else {
                // check if password matches
                user.comparePassword(req.body.password, function (err, isMatch) {
                    if (isMatch && !err) {
                        // if user is found and password is right create a token
                        var token = jwt.encode(user, config.secret);
                        // return the information including token as JSON
                        res.json({success: true, token: 'JWT ' + token});
                    } else {
                        res.send({success: false, msg: 'Authentication failed. Wrong password.'});
                    }
                });
            }
        });
    }

}

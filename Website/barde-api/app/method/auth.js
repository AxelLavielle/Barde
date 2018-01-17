/**
 * @Author: Alexis Miele
 * @Date:   2018-01-16T17:38:06+01:00
 * @Email:  alexis.miele@epitech.eu
 * @Last modified by:   Alexis Miele
 * @Last modified time: 2018-01-17T14:49:29+01:00
 */



/**
 * APLT
 * < arnaud perrault />
 * barde-api - Created on 19/02/2017
 */

var passport    = require("passport");
var passportJWT = require("passport-jwt");
var User        = require("../models/user");
var cfg         = require("../../config/var.js");
var ExtractJwt  = passportJWT.ExtractJwt;
var Strategy    = passportJWT.Strategy;

var params = {
    secretOrKey: cfg.jwt.secret,
    jwtFromRequest: ExtractJwt.fromAuthHeader()
};

module.exports = function () {

    var strategy = new Strategy(params, function (payload, done) {

        console.log(payload);

        User.findOne({
            email: payload.email
        }, function (err, user) {
            if (err) throw err;

            if (!user) {
                return done(new Error("Authentication failed. User not found."), null);
            } else {
                return done(null, {
                    role: user.role,
                    name: user.name,
                    email: user.email,
                    dateOfBirth: user.dateOfBirth
                });
            }
        });

    });

    passport.use(strategy);

    var getToken = function (headers) {
            if (headers && headers.authorization) {
                var parted = headers.authorization.split(' ');
                if (parted.length === 2) {
                    return parted[1];
                } else {
                    return null;
                }
            } else {
                return null;
            }
        };

    return {
        initialize: function () {
            return passport.initialize();
        },
        getToken: getToken,
        admin: function() {
            return function(req, res, next) {
                if (req.user && req.user.role === "Admin")
                    next();
                else
                    res.status(401).send('Unauthorized');
            };
        },
        authenticate: function () {
            return passport.authenticate("jwt", cfg.jwt.session);
        },
        isAuthenticate: function () {
          return function(req, res, next) {
            return passport.authenticate('jwt', cfg.jwt.session, function(err, user, info) {
              if (err) {
                return next(err);
              }
              req.user = user;
              return next()
            })(req, res, next)
          }
        }
    };
};

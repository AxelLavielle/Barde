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
        User.findOne({
            email: payload.email
        }, function (err, user) {
            if (err) throw err;

            if (!user) {
                return done(new Error("Authentication failed. User not found."), null);
            } else {
                return done(null, {
                    email: user.email
                });
            }
        });
    });

    passport.use(strategy);

    return {
        initialize: function () {
            return passport.initialize();
        },
        authenticate: function () {
            return passport.authenticate("jwt", cfg.jwt.session);
        },
        getToken: function (headers) {
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
        }
    };
};
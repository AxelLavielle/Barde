var JwtStrategy = require('passport-jwt').Strategy;
var FacebookStrategy = require('passport-facebook').Strategy;

// load up the user model
var User = require('../app/models/user');
var config = require('../config/db'); // get db config file

module.exports = function(passport) {
    var opts = {};
    opts.secretOrKey = config.secret;

    passport.use(new JwtStrategy(opts, function(jwt_payload, done) {
        User.findOne({id: jwt_payload.id}, function(err, user) {
            if (err) {
                return done(err, false);
            }
            if (user) {
                done(null, user);
            } else {
                done(null, false);
            }
        });
    }));

    passport.use(new FacebookStrategy({
            clientID: "1216456035109321",
            clientSecret: "86206bf12bf0bc96fbafb54992e5a5bb",
            callbackURL: "http://localhost:8080/api/auth/facebook/callback",
            profileFields: ['id', 'emails', 'name'] //This
        },
        function(accessToken, refreshToken, profile, done) {
            done(null, profile);
        }
    ));



// method to serialize user for storage
    passport.serializeUser(function(user, done) {
        done(null, user._id);
    });

// method to de-serialize back for auth
    passport.deserializeUser(function(id, done) {
        User.findById(id, function(err, user) {
            done(err, user);
        });
    });

};
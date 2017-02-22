var jwt = require('jwt-simple');
var User = require('../models/user');
var config = require('../../config/db'); // get db config file
var popupTools = require('popup-tools');
var bcrypt = require('bcrypt');

module.exports = function (apiRoutes, passport) {

    apiRoutes
        .get('/memberinfo', passport.authenticate('jwt', {session: false}), memberInfo)

};

function memberInfo(req, res, next) {
    var token = getToken(req.headers);
    if (token) {
        var decoded = jwt.decode(token, config.secret);
        User.findOne({
            email: decoded.email
        }, function (err, user) {
            if (err) throw err;

            if (!user) {
                return res.status(403).send({success: false, msg: 'Authentication failed. User not found.'});
            } else {
                user.password = "*";
                res.json({success: true, data: user});
            }
        });
    } else {
        return res.status(403).send({success: false, msg: 'No token provided.'});
    }
}

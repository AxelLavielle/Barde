/**
 * APLT
 * < arnaud perrault />
 * barde-api - Created on 19/02/2017
 */

var mongoose = require('mongoose');
var Schema   = mongoose.Schema;
var bcrypt   = require('bcrypt-nodejs');

var UserSchema = new Schema({
    email: {
        type: String,
        lowercase: true,
        unique: true,
        required: true
    },
    password: {
        type: String,
        required: true
    },
    name: {
        firstName: {
            type: String,
            required: true
        },
        lastName: {
            type: String,
            required: true
        },
        userName: {
            type: String,
            required: true,
            unique: true
        }
    },
    dateOfBirth: {
      type: Date,
      required: true
    },
    role: {
        type: String,
        enum: ['Client', 'Admin'],
        default: 'Client'
    }
});

// Saves the user's password hashed
UserSchema.pre('save', function (next) {
    var user = this;
    if (this.isModified('password') || this.isNew) {
        bcrypt.genSalt(10, function (err, salt) {
            if (err) {
                return next(err);
            }
            bcrypt.hash(user.password, salt, function (err, hash) {
                if (err) {
                    return next(err);
                }
                user.password = hash;
                next();
            });
        });
    } else {
        return next();
    }
});

UserSchema.pre('update', function (next) {
    var user = this;
    if (user.getUpdate().$set.password) {
        bcrypt.genSalt(10, function (err, salt) {
            if (err) {
                return next(err);
            }
            bcrypt.hash(user.getUpdate().$set.password, salt, function (err, hash) {
                if (err) {
                    return next(err);
                }
                user.getUpdate().$set.password = hash;
                next();
            });
        });
    } else {
        return next();
    }
});

UserSchema.path('email').validate(function (email) {
  var emailRegex = /^([\w-\.]+@([\w-]+\.)+[\w-]{2,4})?$/;
  return emailRegex.test(email);
}, 'The email format is wrong.')

UserSchema.path('dateOfBirth').validate(function (dateOfBirth) {
  var now = Date.now()
  return dateOfBirth < now;
}, 'The date of birth is wrong.')

// Create method to compare password input to password saved in database
UserSchema.methods.comparePassword = function (pw, cb) {
    bcrypt.compare(pw, this.password, function (err, isMatch) {
        if (err) {
            return cb(err);
        }
        cb(null, isMatch);
    });
};

UserSchema.methods.policyPassword = function (cb) {
  var lowerCaseLetters = /[a-z]/g;
  var upperCaseLetters = /[A-Z]/g;
  var symbols = /\W/g;
  var numbers = /[0-9]/g;
  var minLength = 8;

  if (!lowerCaseLetters.test(this.password))
    return cb({name: 'Password policy', message: 'The password must have at least one lowercase character.'});
  if (!upperCaseLetters.test(this.password))
    return cb({name: 'Password policy', message: 'The password must have at least one uppercase character.'});
  if (!symbols.test(this.password))
    return cb({name: 'Password policy', message: 'The password must have at least one symbol character.'});
  if (!numbers.test(this.password))
    return cb({name: 'Password policy', message: 'The password must have at least one number character.'});
  if (!(this.password.length >= minLength))
    return cb({name: 'Password policy', message: 'The password must have at least eight characters.'});
  cb(null);
};

module.exports = mongoose.model('User', UserSchema);

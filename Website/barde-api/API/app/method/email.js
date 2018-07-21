/**
 * APLT
 * < arnaud perrault />
 * barde-api - Created on 20/02/2017
 */

var nodemailer = require('nodemailer');
var config     = require('../../config/email');

exports.sendEmail = function (name, email, message, callback) {
    var transporter = nodemailer.createTransport(config.smtps);

    var mailOptions = {

        from: name + ' <' + email + '>', // sender address
        to: conf.mail_sendto, // list of receivers
        subject: conf.mail_subject + ' ' + name + ' <' + email + '>', // Subject line
        text: message, // plaintext body
        html: '<p>' + message + '</p>' // html body

    };

    transporter.sendMail(mailOptions, function (error, info) {
        if (error) {
            callback({'success': false});
        }
        callback({'success': true});
    });

}
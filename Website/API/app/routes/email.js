/**
 * APLT
 * < arnaud perrault />
 * barde-api - Created on 14/03/2017
 */

var jwt     = require('jwt-simple');
var request = require("request");
var md5     = require('md5');
var mailer  = require('../method/email');
var auth    = require('../method/auth');
var config  = require('../../config/db');
var Email   = require('../models/email');

module.exports = function (apiRoutes, passport) {
    apiRoutes
        .post('/email/send', sendMail)
        .get('/email', get)
        .put('/email', add)
        .delete('/email', del)
        .patch('/email', update)

};

function get(req, res, next) {

    Email.find(null, function (err, response) {

        if (err) {
            return next(err);
        }

        res.json({data: response});
    });

}

function getOne(req, res, next) {

    Email.findOne({'email': req.body.email}, function (err, response) {

        if (err) {
            return next(err);
        }
        res.status(200).json({data: response});
    });

}


function add(req, res, next) {

    if (!req.body.email) {
        return res.status(400).send({msg: 'No content', data: {message: "Vous devez inscrire votre email."}});
    }

    Email.findOne({'email': req.body.email}, function (err, response) {
        if (err)
            return next(err);
        if (!response) {

            Email.create(req.body, function (err, response) {
                if (err)
                    return next(err);

                addToMailChimp(req.body.email);

                res.status(200).send({
                    msg: "Email added",
                    data: {message: "Votre inscription a bien été pris en compte."}
                });
            });
        }
        else {
            return res.status(304).send({
                msg: 'Email already exists',
                data: {message: "Vous êtes déjà inscrit à nos newsletters !"}
            });
        }
    });

}

function addToMailChimp(email) {
    var options = {
        method: 'PUT',
        url: 'https://us15.api.mailchimp.com/3.0/lists/e05c659b89/members/' + md5(email),
        headers: {
            'cache-control': 'no-cache',
            authorization: 'apikey a551ee72a6096838cc22abdfddc6201c-us15'
        },
        body: JSON.stringify({
            "email_address": email,
            "status_if_new": "subscribed"
        })
    };
    request(options, function (error, response, body) {
        if (error) throw new Error(error);
        console.log(body);
    });
}

function update(req, res, next) {
    Email.update({'email': req.body.email}, function (err, response) {
        if (err)
            return next(err);
        res.status(200).send({msg: 'Field updated'});
    });

}

function del(req, res, next) {
    Email.delete({'email': req.body.email}, function (err, response) {
        if (err)
            return next(err);
        res.status(200).send({msg: 'Email deleted.'});
    });

}

function sendMail(req, res, next) {

    var name    = req.body.name,
        email   = req.body.email,
        message = req.body.message;

    mailer.sendEmail(name, email, message, function (rtn) {
        res.status(200).send(rtn);
    });
}
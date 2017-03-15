/**
 * APLT
 * < arnaud perrault />
 * barde-api - Created on 14/03/2017
 */

/**
 * @apiDefine Email Email
 *
 * All routes for email
 */
var jwt     = require("jwt-simple");
var request = require("request");
var md5     = require("md5");
var mailer  = require("../method/email");
var auth    = require("../method/auth");
var config  = require("../../config/db");
var Email   = require("../models/email");

module.exports = function (apiRoutes, passport) {
    apiRoutes
        .post("/email/send", sendMail)
        .get("/email", get)
        .put("/email", add)
        .delete("/email", del)
        .patch("/email", update)

};

/**
 * @api {get} /email Get all email
 * @apiName GetAllEmail
 * @apiGroup Email
 *
 * @apiErrorExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "emails": allEmails
 *       }
 *     }
 */
function get(req, res, next) {

    Email.find(null, function (err, response) {

        if (err) {
            return next(err);
        }

        res.status(200).json({msg: "Success", data: {emails: response}});
    });

}

/**
 * @api {put} /email/ Add email
 * @apiGroup Email
 *
 * @apiSuccess {String} email Email to add.
 *
 * @apiErrorExample 400 - No email
 *     {
 *       "msg": "No content"
 *       "data": {
 *          "message": "Vous devez inscrire votre email."
 *       }
 *     }
 *
 *  @apiErrorExample 200 - No email
 *     {
 *       "msg": "Content added"
 *       "data": {
 *          "message": "Votre inscription a bien été pris en compte."
 *       }
 *     }
 *
 *  @apiErrorExample 304 - Already exists
 *     {
 *       "msg": "Content already exists"
 *       "data": {
 *          "message": "Vous êtes déjà inscrit à nos newsletters !"
 *       }
 *     }
 */
function add(req, res, next) {

    if (!req.body.email) {
        return res.status(400).send({msg: "No content", data: {message: "Vous devez inscrire votre email."}});
    }

    Email.findOne({"email": req.body.email}, function (err, response) {
        if (err)
            return next(err);
        if (!response) {

            Email.create(req.body, function (err, response) {
                if (err)
                    return next(err);

                addToMailChimp(req.body.email);

                res.status(200).send({
                    msg: "Content added",
                    data: {message: "Votre inscription a bien été pris en compte."}
                });
            });
        }
        else {
            return res.status(304).send({
                msg: "Content already exists",
                data: {message: "Vous êtes déjà inscrit à nos newsletters !"}
            });
        }
    });

}

function addToMailChimp(email) {
    var options = {
        method: "PUT",
        url: "https://us15.api.mailchimp.com/3.0/lists/e05c659b89/members/" + md5(email),
        headers: {
            "cache-control": "no-cache",
            authorization: "apikey a551ee72a6096838cc22abdfddc6201c-us15"
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

/**
 * @api {patch} /email/ Update email
 * @apiName UpdateEmail
 * @apiGroup Email
 *
 *  @apiErrorExample 200 - Success
 *     {
 *       "msg": "Content updated"
 *     }
 */
function update(req, res, next) {
    Email.update({"email": req.body.email}, function (err, response) {
        if (err)
            return next(err);
        res.status(200).send({msg: "Content updated"});
    });

}


/**
 * @api {delete} /email/ Delete email
 * @apiName DeleteEmail
 * @apiGroup Email
 *
 *  @apiErrorExample 200 - Success
 *     {
 *       "msg": "Content deleted"
 *     }
 */
function del(req, res, next) {
    Email.delete({"email": req.body.email}, function (err, response) {
        if (err)
            return next(err);
        res.status(200).send({msg: "Content deleted"});
    });

}

/**
 * @api {post} /email/send Send email
 * @apiName SendEmail
 * @apiGroup Email
 *
 * @apiSuccess {String} email Email to delete.
 *
 * @apiErrorExample 200 - Success
 *     {
 *       "msg": "Content send"
 *     }
 *
 * @apiErrorExample 400 - Success
 *     {
 *       "msg": "Error"
 *     }
 */
function sendMail(req, res, next) {

    var name    = req.body.name,
        email   = req.body.email,
        message = req.body.message;

    mailer.sendEmail(name, email, message, function (rtn) {
        if (rtn.success)
            res.status(200).send({msg: "Content send"});
        else
            res.status(400).send({msg: "Error"});

    });
}

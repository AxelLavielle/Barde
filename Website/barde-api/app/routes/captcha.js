/**
 * APLT
 * < arnaud perrault />
 * barde-api - Created on 22/02/2017
 */

/**
 * @apiDefine Captcha Captcha
 *
 * All routes for captcha
 */

var request = require("request");

module.exports = function (apiRoutes, passport) {
    apiRoutes
        .post('/captcha/verify', verifyCaptcha)

};


/**
 * @api {post} /captcha/verify Verify if client is bot
 * @apiName Verify
 * @apiGroup Captcha
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "response": ""
 *     }
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "message": ""
 *       }
 *     }
 *
 * @apiErrorExample 400 - Error
 *     {
 *       "msg": "Error"
 *       "data": {
 *          "message": ""
 *       }
 *     }
 */
function verifyCaptcha(req, res, next) {

    var options = "https://www.google.com/recaptcha/api/siteverify?secret=6LfJQBYUAAAAAJIkpcszGK1vwNxXoPhbN3UGxr_O&response=" + req.body.response;

    request(options, function (error, response, body) {

        if (error)
            res.status(400).send("");

        res.status(200).send("");

        console.log(body);
    });

}

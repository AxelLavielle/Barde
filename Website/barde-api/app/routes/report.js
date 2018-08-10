/**
 * @Author: Alexis Miele
 * @Date:   2018-01-16T19:01:20+01:00
 * @Email:  alexis.miele@epitech.eu
 * @Last modified by:   Alexis Miele
 * @Last modified time: 2018-01-17T14:49:45+01:00
 */



/**
 * APLT
 * < arnaud perrault />
 * API - Created on 21/03/2017
 */

/**
 * @apiDefine Report Reports
 *
 * All routes for reports
 */

var config     = require('../../config/var');
var methodAuth = require('../method/auth')();

var Report = require('../models/report');

module.exports = function (apiRoutes, passport) {

    apiRoutes
        .get('/report', methodAuth.authenticate(), methodAuth.admin(), get)
        .get('/report/count', methodAuth.authenticate(), methodAuth.admin(), getNumber)
        .get('/report/:perPage/:page', methodAuth.authenticate(), methodAuth.admin(), getByPage)
        .post("/report", methodAuth.authenticate(), post)
};


/**
 * @api {get} /report Get all reports
 * @apiGroup Report
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "reports": []
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function get(req, res, next) {

    Report.find().populate('user', 'email').exec(function (err, response) {

        if (err) {
            return next(err);
        }

        res.status(200).json({msg: "Success", data: {reports: response}});
    });
}

/**
 * @api {get} /report/count Get number of reports
 * @apiGroup Report
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "count": Number
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function getNumber(req, res, next) {

    Report.count(null, function (err, response) {

        if (err) {
            return next(err);
        }

        res.status(200).json({msg: "Success", data: {count: response}});
    });
}

/**
 * @api {get} /report/:perPage/:page Get reports by page
 * @apiGroup Report
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "reports": [],
 *          "page": Number,
 *          "count": Number
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function getByPage(req, res, next) {

    var perPage = Math.max(0, req.param('perPage'));
    var page    = Math.max(0, req.param('page'));


    Report.find()
        .populate('user', 'email').limit(perPage).skip(perPage * page).exec(function (err, reports) {
        Report.count().exec(function (err, count) {
            res.status(200).json({msg: "Success", data: {reports: reports, page: page + 1, count: count / perPage}});
        })
    })
}

/**
 * @api {post} /report New report
 * @apiGroup Report
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "description": "",
 *     }
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Content created"
 *       "data": {
 *          "message": "Report saved."
 *       }
 *     }
 *
 * @apiErrorExample 400 - One param is empty
 *     {
 *       "msg": "No content"
 *       "data": {
 *          "message": param + " cannot be empty."
 *       }
 *     }
 *
 *  @apiErrorExample 400 - Device param is wrong
 *     {
 *       "msg": "Content validation"
 *       "data": {
 *          "message": "The device is wrong."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function post(req, res, next) {
    if (!req.body.description) {
        res.status(400).send({msg: "No content", data: {message: "Description cannot be empty."}});
    } else if (!req.body.device) {
        res.status(400).send({msg: "No content", data: {message: "Device cannot be empty."}});
    } else if (req.body.device != 'Android' && req.body.device != 'Windows' && req.body.device != 'iOS') {
        res.status(400).send({msg: "Content validation", data: {message: "The device is wrong."}});
    } else {
        var newReport = new Report({
            user: req.user,
            description: req.body.description,
            device: req.body.device
        });

        newReport.save(function (err) {
            if (err) {
              next(err);
            } else {
              res.status(200).send({
                  msg: "Content created",
                  data: {message: "Report saved."}
              });
            }
        });
    }

}

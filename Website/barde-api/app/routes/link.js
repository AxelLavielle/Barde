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
 * @apiDefine Link Links
 *
 * All routes for links
 */

var config     = require('../../config/var');
var methodAuth = require('../method/auth')();

var Link = require('../models/link');

module.exports = function (apiRoutes, passport) {

    apiRoutes
        .get('/link', get)
        .delete('/link', methodAuth.authenticate(), methodAuth.admin(), deleteLink)
        .put("/link", methodAuth.authenticate(), methodAuth.admin(), update)
        .post("/link", methodAuth.authenticate(), methodAuth.admin(), post)
};


/**
 * @api {get} /link Get all links
 * @apiGroup Link
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "link": []
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

    Link.find().exec(function (err, response) {

        if (err) {
            return next(err);
        }

        res.status(200).json({msg: "Success", data: {links: response}});
    });
}

/**
 * @api {post} /link New link
 * @apiGroup Link
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "link": "",
 *       "device": "",
 *     }
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Content created"
 *       "data": {
 *          "message": "Link saved."
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
    if (!req.body.link) {
        res.status(400).send({msg: "No content", data: {message: "Link cannot be empty."}});
    } else if (!req.body.device) {
        res.status(400).send({msg: "No content", data: {message: "Device cannot be empty."}});
    } else {
        var newLink = new Link({
            link: req.body.link,
            device: req.body.device
        });

        newLink.save(function (err) {
            if (err) {
              res.status(400).send({msg: "Content validation", data: {message: "The device is wrong."}});
              next(err);
            } else {
              res.status(200).send({
                  msg: "Content created",
                  data: {message: "Link saved."}
              });
            }
        });
    }

}

/**
 * @api {put} /link Update link
 * @apiGroup Link
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "link": "",
 *       "device": ""
 *     }
 *
 *  @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Content updated"
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
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item."
 *       "data": {
 *          "message": "Link not exists."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function update(req, res, next) {
  if (!req.body.link) {
    res.status(400).send({msg: "No content", data: {message: "Link cannot be empty."}});
  } else if (!req.body.device) {
    res.status(400).send({msg: "No content", data: {message: "Device cannot be empty."}});
  } else {
    var updateVal = {};
    updateVal["link"] = req.body.link
    Link.update({
      "device": req.body.device
    }, {$set: updateVal}, function (err, response) {
      if (err) {
        return next(err);
      } else {
        if (response.n == 0) {
          res.status(404).json({msg: "Can't find item.", message: {users: "Link not exists."}});
        } else {
          res.status(200).send({msg: "Content updated"});
        }
      }
    });
  }
}

/**
 * @api {delete} /link Delete link
 * @apiGroup Link
 *
 * @apiParamExample {json} Request-Example:
 *     {
 *       "device": "",
 *     }
 *
 * @apiSuccessExample 200 - Success
 *     {
 *       "msg": "Success"
 *       "data": {
 *          "message": "Link deleted."
*        }
 *     }
 *
 * @apiErrorExample 404 - Not found
 *     {
 *       "msg": "Can't find item"
 *       "data": {
 *          "message": "Link not exists."
 *       }
 *     }
 *
 * @apiErrorExample 401 - Unauthorized
 *     {
 *       "Unauthorized"
 *     }
 *
 */
function deleteLink(req, res, next) {
  if (!req.body.device) {
    res.status(400).send({msg: "No content", data: {message: "Device cannot be empty."}});
  } else {
    Link.findOneAndRemove({
      "device": req.body.device
    }, function (err, response) {
      if (err)
        return next(err);
      if (!response) {
        res.status(404).send({msg: "Can't find item", data: {message: "Link not exists."}});
        return next(err);
      }
      res.status(200).send({msg: "Success", data: {message: "Link deleted."}});
    });
  }
}

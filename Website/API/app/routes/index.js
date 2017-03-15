/**
 * APLT
 * < arnaud perrault />
 * barde-api - Created on 14/03/2017
 */

/**
 * Ce module charge dynamiquement toutes les modules de routes du dossier routes
 */
'use strict';
var fs   = require('fs');
var path = require('path');

module.exports = function (app, passport, admin) {
    fs.readdirSync('./app/routes').forEach(function (file) {
        // Ne pas charger le fichier index et le dossier unused
        if (file === path.basename(__filename) || path.extname(file) != '.js') {
            return;
        }

        require('./' + file)(app, passport);

    });
};

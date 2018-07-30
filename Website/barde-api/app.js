/**
 * APLT
 * < arnaud perrault />
 * barde-api - Created on 16/02/2017
 */

var express    = require('express');
var session    = require('express-session');
var mongoose   = require('mongoose');
var bodyParser = require('body-parser');
var morgan     = require('morgan');
var passport   = require('passport');
var bcrypt     = require('bcrypt-nodejs');
var config     = require('./config/db');
var app        = express();

var port = process.env.PORT || 3000;

app.use(express.static(__dirname));

app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());

app.use(passport.initialize());

// Log to console
app.use(morgan('dev'));

// Connect to mongoDB
mongoose.connect(config.database);

app.get('/', function (req, res) {
    res.sendFile('index.html');
});

app.all('/*', function (req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE,PATCH');
    res.header("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Authorization");
    next();
});

app.listen(port);
console.log('Server started >> http://localhost:' + port + " <<");

var apiRoutes = express.Router();
require('./app/routes')(apiRoutes, passport);


app.use('/', apiRoutes);

var express     = require('express');
var session     = require('express-session');
var bodyParser  = require('body-parser');
var morgan      = require('morgan');
var mongoose    = require('mongoose');
var passport    = require('passport');
var config      = require('./config/db'); // get db config file
var app         = express();

var port        = process.env.PORT || 3000;

app.use(express.static(__dirname));

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

// log to console
app.use(morgan('dev'));
mongoose.connect(config.database);
app.use(passport.initialize());


// (GET http://localhost:8080)
app.get('/', function(req, res) {
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

require('./config/passport')(passport);

var apiRoutes = express.Router();
require('./app/routes')(apiRoutes, passport);


app.use('/', apiRoutes);
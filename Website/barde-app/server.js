var app = require('http').createServer(handler)
var io = require('socket.io')(app);
var fs = require('fs');

app.listen(8081);

function handler (req, res) {
  fs.readFile(__dirname + '/index.html',
    function (err, data) {
      if (err) {
        res.writeHead(500);
        return res.end('Error loading index.html');
      }

      res.writeHead(200);
      res.end(data);
    });
}

io.on('message', function (message) {
  socket.emit('message', {message: 'play'});

  console.log('Un client me parle ! Il me dit : ' + message);
});

io.on('connection', function (socket) {
  socket.emit('connected', {message: 'you are now connected'});
  socket.on('message', function (data) {
    console.log(data);
  });
});

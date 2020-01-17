#!/usr/bin/env node

/**
 * Module dependencies.
 */

//var app = require('./app');
var path = require('path');

var debug = require('debug')('giamsatmoitruong:server');
var http = require('http');
var express = require("express");
var app = express();

var testrouter = require('./routes/index');
var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
/**
 * Get port from environment and store in Express.
 */


var port = normalizePort(process.env.PORT || '3000');
app.set('port', port);
/**
 * Create socket.io server.
 */


var server = require("http").Server(app);
var io = require("socket.io")(server);
/**
 * Listen on provided port, on all network interfaces.
 */


app.use(express.static("public"));
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'hbs');

server.listen(port);
/**
* 
*/



app.use('/', indexRouter);
app.use('/users', usersRouter);

io.on("connection", function(socket){
  console.log("co nguoi ket noi."+socket.id);

  socket.on("disconnect", function(){
    console.log(socket.id + " ngat ket noi")
  });

  // socket.on('send-data', (data) =>{
  //   console.log(data);
  //   console.log(socket.id);
  // });


  socket.on("sendfirst", function(data){
    console.log(socket.id + " send "+data);
  });
});





















/**
 * Normalize a port into a number, string, or false.
 */

function normalizePort(val) {
  var port = parseInt(val, 10);

  if (isNaN(port)) {
    // named pipe
    return val;
  }

  if (port >= 0) {
    // port number
    return port;
  }

  return false;
}

/**
 * Event listener for HTTP server "error" event.
 */

function onError(error) {
  if (error.syscall !== 'listen') {
    throw error;
  }

  var bind = typeof port === 'string'
    ? 'Pipe ' + port
    : 'Port ' + port;

  // handle specific listen errors with friendly messages
  switch (error.code) {
    case 'EACCES':
      console.error(bind + ' requires elevated privileges');
      process.exit(1);
      break;
    case 'EADDRINUSE':
      console.error(bind + ' is already in use');
      process.exit(1);
      break;
    default:
      throw error;
  }
}

/**
 * Event listener for HTTP server "listening" event.
 */

function onListening() {
  var addr = server.address();
  var bind = typeof addr === 'string'
    ? 'pipe ' + addr
    : 'port ' + addr.port;
  debug('Listening on ' + bind);
}
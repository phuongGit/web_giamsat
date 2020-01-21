var fs = require('fs');
var url = require('url');
var http = require('http');
var querystring = require('querystring');
var db = []; //database
//---------------------------------------------------------------------------------------------
//create database
var mysql = require('mysql');

var con = mysql.createConnection({
  host: "127.0.0.1",
  user: "root",
  password: "!@aA12345",
  database: "arduino"
});

//---------------------------------------------------------------------------------------------
// function gửi yêu cầu(response) từ phía server hoặc nhận yêu cầu (request) của client gửi lên
function requestHandler(request, response) {
    
    // Giả sử địa chỉ nhận được http://192.168.1.7:8000/update?temp=30&humd=40
    var uriData = url.parse(request.url);
    var pathname = uriData.pathname;          // /update?
    var query = uriData.query;                // temp=30.5&hum=80
    var queryData = querystring.parse(query); // queryData.temp = 30.5, queryData.humd = 40



    //-----------------------------------------------------------------------------------------
    if (pathname == '/update') {
        var newData = {
            temp: queryData.temp,
            humd: queryData.humd,
            time: new Date()
        };
        db.push(newData);
        console.log(newData);
        response.end();
            con.connect(function(err) {
        
            var sql = "INSERT INTO devices (temp, humd) VALUES ('"+queryData.temp+"','"+queryData.humd+"')";
            con.query(sql, function (err, result) {
            if (err) throw err;
                console.log("1 record inserted");
            });
    });
    //-----------------------------------------------------------------------------------------
    } else if (pathname == '/get') {
        response.writeHead(200, {
            'Content-Type': 'application/json'
        });
        response.end(JSON.stringify(db));
        db = [];
    //-----------------------------------------------------------------------------------------
    } else { 
        fs.readFile('./index.html', function(error, content) {
            response.writeHead(200, {
                'Content-Type': 'text/html'
            });
            response.end(content);
        });
    }
    //-----------------------------------------------------------------------------------------
}
var server = http.createServer(requestHandler);
server.listen(8000); 
console.log('Server listening on port 8000');
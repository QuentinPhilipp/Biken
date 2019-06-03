/*
var http = require('http');
var fs = require('fs');

// Chargement du fichier index.html affiché au client
var server = http.createServer(function(req, res) {
    /*fs.readFile('./index.html', 'utf-8', function(error, content) {
        res.writeHead(200, {"Content-Type": "text/html"});
        res.end(content);
    });*/
    //res.writeHead(200);
   // res.end('serveur is here...')
//});
/*
// Chargement de socket.io
var io = require('socket.io').listen(server);

// Quand un client se connecte, on le note dans la console
io.sockets.on('connection', function (socket) {
    console.log('Un client est connecté !');
});

io.sockets.on('connection', function (socket) {
        socket.emit('message', 'Vous êtes bien connecté !');
		// Quand le serveur reçoit un signal de type "message" du client    
		socket.on('message', function (message) {
    	console.log('Un client me parle ! Il me dit : ' + message);
		});	
});

socket.emit('message','Hello!');

server.listen(8080);*/

//card.html envoi sur un port --> récupére donnée dans tableau/ex
//Puis sur un autre port, on envoie donnée sauvegardée au qml
var data = [];

const WebSocket1 = require('ws');
const wss1 = new WebSocket1.Server({ port: 8080 });
//const ws = new WebSocket('ws://localhost:8080');
wss1.on('connection', function connection(ws) {
  //quand on a un message o l'enregistre
  ws.on('message', function incoming(message) {
    var donnee =message.substr(6);
    console.log(donnee);
    data.push(donnee);
    console.log(data);
  });
});

//toutes les données sont alors dans data
//on envoie alors data au QML

const WebSocket2 = require('ws');
const wss2 = new WebSocket2.Server({port : 1234});
//envoi qu'à la connection
wss2.on('connection',function connection(ws) {
  var l = data.length;
  ws.send(data[l-1]);
  console.log('data a été envoyé to Qt via JS');
});



//avec ça quand Qt se connecte, il récupère la dernière donnée

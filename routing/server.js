//card.html envoi sur un port --> récupére donnée dans tableau/ex
//Puis sur un autre port, on envoie donnée sauvegardée au qml qui mettre à jour la case correspondante suivant la case concernée (identifié par 0 ou 1 lors de l'envoi à QML)
var data = [];

const WebSocket1 = require('ws');
const wss1 = new WebSocket1.Server({ port: 8080 });
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
  //console.log('data a été envoyé to Qt via JS');
});



//avec ça quand Qt se connecte, il récupère la dernière donnée

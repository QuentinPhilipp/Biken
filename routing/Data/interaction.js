var markers =[];


function haveMap(){

	for(item in window) {

		if(item[0]=='m' && item[1]=='a' && item[2]=='p' && item[3]=="_")				//récupération de l'ID de notre map courante
		{
		return item;
		}
	}
}


function haveMarkers(){
	for(item in window) {

		if(item[0]=='m' && item[1]=='a' && item[2]=='r' && item[3]=="k" && item[4]=="e" && item[5]=="r" && item[6]=="_")			//on récupère maintenant tous les marqueurs de la carte
		{
		markers.push(item)	;
		}
	}
}

function haveLayer(){
    for(item in window) {
        if(item[0]=='t' && item[1]=='i' && item[2]=='l' && item[3]=="e" && item[4]=="_" && item[5]=="l" && item[6]=="a")
        {
        return item
        }
            }
}

haveMarkers() // on récupére alors tout nos marqueurs
var layer = window[haveLayer()]
var map = window[haveMap()]

for(var i=0 ; i<markers.length ;++i)
{
	m = window[markers[i]]												//Gestion du mouvement des marqueurs de la carte
	m.on('dragend', function(e) {
    		console.log(m.getLatLng()); } )								//window[string] recréé l'objet associé à la string
}

var Esri_WorldImagery = L.tileLayer('http://server.arcgisonline.com/ArcGIS/rest/services/World_Imagery/MapServer/tile/{z}/{y}/{x}', {
    attribution: 'Tiles &copy; Esri &mdash; Source: Esri, i-cubed, USDA, USGS, ' +
    'AEX, GeoEye, Getmapping, Aerogrid, IGN, IGP, UPR-EGP, and the GIS User Community'
    });


//ajout du controlzoom
L.control.zoom({
     position:'topright'
}).addTo(map);

var baseLayers = {
    "Satellite": Esri_WorldImagery,
    "Plan": layer
    };


var layerControl = L.control.layers(baseLayers);                //avec ce layer --> peut choisir vue satellite ect --> faire pour retourner à la vue de base
layerControl.addTo(map);

var exampleSocket = new WebSocket("ws://localhost:8080");
exampleSocket.onopen = function (event) { 
                //console.log("Connexion serveur");
                exampleSocket.send("");             //quand la carte avec l'itinéraire est chargée, on se connecte au serveur pour lui envoyer un message vide

             }









/*
mymap.on('click', function(e) {
    //alert("Lat, Lon : " + e.latlng.lat + ", " + e.latlng.lng)				//on récupére lon/lat au clic de la souris
    lat = e.latlng.lat
    lon = e.latlng.lng
    console.log(lat,lon)

    var marker= L.marker(													//on lui demande de créer un marqueur à ce moment là
            [lat, lon],
            {
                icon: new L.Icon.Default(),
                draggable: true,
                autoPan: true,
                }
            ).addTo(mymap);
    console.log(marker.getLatLng())
}); */

    //alert("Lat, Lon : " + e.latlng.lat + ", " + e.latlng.lng)				//on récupére lon/lat au clic de la souris

/*
    marker.on('dragend', function(e) {
    		console.log(marker.getLatLng())
    	}
    	)
    */

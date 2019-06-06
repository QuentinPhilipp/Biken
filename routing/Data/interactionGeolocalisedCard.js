var markers =[];
var clics = 0;

function haveMap(){

	for(item in window) {

		if(item[0]=='m' && item[1]=='a' && item[2]=='p' && item[3]=="_")				//récupération de l'ID de notre map courante
		{
		return item;
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


var map =window[haveMap()]  //on récupère notre carte
var layer = window[haveLayer()] //récupère notre layer

//ajout du controlzoom
L.control.zoom({
     position:'topright'
}).addTo(map);

//Ajout d'un layer sur la carte

var Esri_WorldImagery = L.tileLayer('http://server.arcgisonline.com/ArcGIS/rest/services/World_Imagery/MapServer/tile/{z}/{y}/{x}', {
    attribution: 'Tiles &copy; Esri &mdash; Source: Esri, i-cubed, USDA, USGS, ' +
    'AEX, GeoEye, Getmapping, Aerogrid, IGN, IGP, UPR-EGP, and the GIS User Community'
    });



var baseLayers = {
    "Satellite": Esri_WorldImagery,
    "Plan": layer
    };

var layerControl = L.control.layers(baseLayers);				//avec ce layer --> peut choisir vue satellite ect 
layerControl.addTo(map);

//on ne peut en créer que deux : arrivée et départ

//on connaît le nombre de marqueurs au début, qui est forément nul


var exampleSocket = new WebSocket("ws://localhost:8080");
exampleSocket.onopen = function (event) {
                console.log("Connexion serveur");
                exampleSocket.send("connecte au serveur")

             }


//creation de deux marqueurs max(arrivée t départ). Chacun envoyant ses coordonnées à son déplacement.
function MarkersCreation(){
	map.on('click', function(e) {
    	//alert("Lat, Lon : " + e.latlng.lat + ", " + e.latlng.lng)				//on récupére lon/lat au clic de la souris
    	lat = e.latlng.lat
    	lon = e.latlng.lng
    	c=markers.length

    	if(c<2){
			var marker= L.marker(													//on lui demande de créer un marqueur à ce moment là
        		[lat, lon],
          	 	{
            		    icon: new L.Icon.Default(),
            	    	draggable: true,
                		autoPan: true,
                		}
            		).addTo(map);
			marker.on('drag', function(e) {
				if(marker==markers[0])
				{
  				exampleSocket.send(marker.getLatLng().toString()+'0');						//on identifie les deux marqueurs par 0 ou 1 en fin de string
  				}                                                                 //marqueurs ont propriété d'envoyer leurs coordonnées lorsqu'ils sont bougés
  				else{
  					exampleSocket.send(marker.getLatLng().toString()+'1');
  				}
  				//console.log("envoi")
   			});
			//console.log(marker.getLatLng())
			exampleSocket.send(marker.getLatLng().toString()+c.toString());
			markers.push(marker)
			}

	else {
		alert("Vous avez déjà deux points");
	}

	console.log(markers);
	console.log(markers.length)
	console.log(c);
	});
}


MarkersCreation();

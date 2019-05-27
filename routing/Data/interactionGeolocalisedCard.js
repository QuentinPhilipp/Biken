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
var layer = window[haveLayer()]
//Ajout d'un layer sur la carte

var Esri_WorldImagery = L.tileLayer('http://server.arcgisonline.com/ArcGIS/rest/services/World_Imagery/MapServer/tile/{z}/{y}/{x}', {
    attribution: 'Tiles &copy; Esri &mdash; Source: Esri, i-cubed, USDA, USGS, ' +
    'AEX, GeoEye, Getmapping, Aerogrid, IGN, IGP, UPR-EGP, and the GIS User Community'
    });

    

var baseLayers = {
    "Si tu cliques...": Esri_WorldImagery,
    "Tu vas ...": layer
    };

var layerControl = L.control.layers(baseLayers);				//avec ce layer --> peut choisir vue satellite ect --> faire pour retourner à la vue de base
layerControl.addTo(map);
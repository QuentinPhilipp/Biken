var polyline;

function haveMap(){

	for(item in window) {

		if(item[0]=='m' && item[1]=='a' && item[2]=='p' && item[3]=="_")				//récupération de l'ID de notre map courante
		{
		return item;
		}
	}
}

function havePolyline(){
	for(item in window) {

		if(item[0]=='p' && item[1]=='o' && item[2]=='l' && item[3]=="y" && item[4]=="_" && item[5]=="l" && item[6]=="i")			//on récupère maintenant tous les marqueurs de la carte
		{
		return item	;					
		}
	}
}

var map = window[haveMap()];

polyline = window[havePolyline()];

polyline.toGeoJSON();

console.log(polyline.toGeoJSON());
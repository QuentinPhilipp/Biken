import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtLocation 5.6
import QtPositioning 5.6
import "helper.js" as Helper
import "map"
import "weatherAddon"
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4
import QtWebEngine 1.7


ApplicationWindow {

    id: mainWaindow

    property var map


    visibility: "Maximized"
    minimumWidth: Screen.width/2
    color: "#adb9c8"
    minimumHeight: 800
    visible: true
    FontLoader{
        id: comfortaalight
        source: "qrc:/comfortaa/Comfortaa-Light.ttf"
    }

    menuBar: MenuBar {
        Menu {
            title: "Fichier"
            MenuItem { text: "Open" }
            MenuItem { text: "Close" }
        }

        Menu {
            title: "Paramètres"
            MenuItem{
                text: "Département"

                onClicked :popupselectdepartment.open()
            }
        }
        Menu {
            title: "Export"
        }
        Menu {
            title: "Credit"
        }
    }

    Popup {
        id: popupselectdepartment
        x: 50
        y: 50
        width: 900
        height: 700
        Column {
            CheckBox {
                id : ain
                text : "Ain"
            }
            CheckBox {
                id : aisne
                text : "Aisne"
            }
            CheckBox {
                id : allier
                text : "Allier"
            }
            CheckBox {
                id : alpesdehauteprovence
                text : "Alpes-de-Haute-Provence"
            }
            CheckBox {
                id : hautesalpes
                text : "Hautes-Alpes"
            }
            CheckBox {
                id : alpesmaritimes
                text : "Alpes-Maritimes"
            }
            CheckBox {
                id : ardeche
                text : "Ardèche"
            }
            CheckBox {
                id : ardennes
                text : "Ardennes"
            }
            CheckBox {
                id : ariege
                text : "Ariège"
            }
            CheckBox {
                id : aube
                text : "Aube"
            }
            CheckBox {
                id : aude
                text : "Aude"
            }
            CheckBox {
                id : aveyron
                text : "Aveyron"
            }
            CheckBox {
                id : bouchesdurhone
                text : "Bouches-du-Rhône"
            }
            CheckBox {
                id : calvados
                text : "Calvados"
            }

            CheckBox {
                id : cantal
                text : "Cantal"
            }
            CheckBox {
                id : charente
                text : "Charente"
            }
            CheckBox {
                id : charenteMaritime
                text : "Charente-Maritime"
            }
            CheckBox {
                id : cher
                text : "Cher"
            }
            CheckBox {
                id : corrèze
                text : "Corrèze"
            }
            CheckBox {
                id : côtedOr
                text : "Calvados"
            }

            CheckBox {
                id : côtesdArmor
                text : "Côtes-d Armor"
            }
            CheckBox {
                id : creuse
                text : "Creuse"
            }
            CheckBox {
                id : dordogne
                text : "Dordogne"
            }
            CheckBox {
                id : doubs
                text : "Doubs"
            }
            CheckBox {
                id : drôme
                text : "Drôme"
            }
            CheckBox {
                id : eure
                text : "Eure"
            }
            CheckBox {
                id : eureetLoir
                text : "Eure-et-Loir"
            }
            CheckBox {
                id : finistère
                text : "Finistère"
            }
            CheckBox {
                id : gard
                text : "gard"
            }
            CheckBox {
                id : hautegaronne
                text : "Haute-garonne"
            }
        }
        Column {
            CheckBox {
                id : gers
                text : "Gers"
            }
            CheckBox {
                id : gironde
                text : "Gironde"
            }
            CheckBox {
                id : deuxBHauteCorse
                text : "2BHaute-Corse"
            }
            CheckBox {
                id : deuxACorsedusud
                text : "2ACorse du sud"
            }
            CheckBox {
                id : hérault
                text : "Hérault"
            }
            CheckBox {
                id : illeetVilaine
                text : "Ille-et-Vilaine"
            }
            CheckBox {
                id : indre
                text : "Indre"
            }
            CheckBox {
                id : indreetLoire
                text : "Indre-et-Loire"
            }
            CheckBox {
                id : isère
                text : "Isère"
            }
            CheckBox {
                id : jura
                text : "Jura"
            }
            CheckBox {
                id : landes
                text : "Landes"
            }

            CheckBox {
                id : loiretCher
                text : "Loir-et-Cher"
            }
            CheckBox {
                id : loire
                text : "Loire"
            }
            CheckBox {
                id : hauteLoire
                text : "Haute-Loire"
            }
            CheckBox {
                id : loireAtlantique
                text : "Loire-Atlantique"
            }
            CheckBox {
                id : loiret
                text : "Loiret"
            }
            CheckBox {
                id : lot
                text : "Lot"
            }
            CheckBox {
                id : lotetGaronne
                text : "Lot-et-Garonne"
            }
            CheckBox {
                id : lozère
                text : "Lozère"
            }
            CheckBox {
                id : maineetLoire
                text : "Maine-et-Loire"
            }
            CheckBox {
                id : manche
                text : "Manche"
            }
            CheckBox {
                id : marne
                text : "Marne"
            }

            CheckBox {
                id : hauteMarne
                text : "Haute-Marne"
            }
            CheckBox {
                id : mayenne
                text : "Mayenne"
            }
            CheckBox {
                id : meurtheetMoselle
                text : "Meurthe-et-Moselle"
            }
            CheckBox {
                id : meuse
                text : "Meuse"
            }
            CheckBox {
                id : morbihan
                text : "Morbihan"
            }

            CheckBox {
                id : moselle
                text : "Moselle"
            }
            CheckBox {
                id : nièvre
                text : "Nièvre"
            }
            CheckBox {
                id : nord
                text : "Nord"
            }
        }
        Column {
            CheckBox {
                id : oise
                text : "Oise"
            }
            CheckBox {
                id : orne
                text : "Orne"
            }
            CheckBox {
                id : pasdeCalais
                text : "Pas-de-Calais"
            }

            CheckBox {
                id : puydeDôme
                text : "Puy-de-Dôme"
            }
            CheckBox {
                id : pyrénéesAtlantiques
                text : "Pyrénées-Atlantiques"
            }
            CheckBox {
                id : hautesPyrénées
                text : "Hautes-Pyrénées"
            }
            CheckBox {
                id : pyrénéesOrientales
                text : "Pyrénées-Orientales"
            }
            CheckBox {
                id : basRhin
                text : "Bas-Rhin"
            }

            CheckBox {
                id : hautRhin
                text : "Haut-Rhin"
            }
            CheckBox {
                id : rhône
                text : "Rhône"
            }
            CheckBox {
                id : hauteSaône
                text : "Haute-Saône"
            }
            CheckBox {
                id : saôneetLoire
                text : "Saône-et-Loire"
            }
            CheckBox {
                id : sarthe
                text : "Sarthe"
            }

            CheckBox {
                id : savoie
                text : "Savoie"
            }
            CheckBox {
                id : hauteSavoie
                text : "Haute-Savoie"
            }
            CheckBox {
                id : paris
                text : "Paris"
            }CheckBox {
                id : seineMaritime
                text : "Seine-Maritime"
            }
            CheckBox {
                id : seineetMarne
                text : "Seine-et-Marne"
            }
            CheckBox {
                id : yvelines
                text : "yvelines"
            }

            CheckBox {
                id : deuxSèvres
                text : "Deux-Sèvres"
            }
            CheckBox {
                id : somme
                text : "Somme"
            }
            CheckBox {
                id : tarn
                text : "Tarn"
            }
            CheckBox {
                id : tarnetGaronne
                text : "Tarn-et-Garonne"
            }
            CheckBox {
                id : varr
                text : "Var"
            }

            CheckBox {
                id : vaucluse
                text : "Vaucluse"
            }
            CheckBox {
                id : vendée
                text : "Vendée"
            }
            CheckBox {
                id : vienne
                text : "Vienne"
            }
            CheckBox {
                id : hauteVienne
                text : "Haute-Vienne"
            }
            CheckBox {
                id : vosges
                text : "Vosges"
            }

            CheckBox {
                id : yonne
                text : "Yonne"
            }
        }
        Column {
            CheckBox {
                id : territoiredeBelfort
                text : "Territoire de Belfort"
            }
            CheckBox {
                id : essonne
                text : "Essonne"
            }
            CheckBox {
                id : hautsdeSeine
                text : "Hauts-de-Seine"
            }
            CheckBox {
                id : seinesaintdenis
                text : "Seine-Saint-Denis"
            }
            CheckBox {
                id : valdeMarne
                text : "Val-de-Marne"
            }
            CheckBox {
                id : valdOise
                text : "Val-d Oise"
            }

            Button {
                id : refreshDatabase
                onClicked : {
                    if (ain.checked == true){
                        dataManager.extendDatabase('01')}
                    if (aisne.checked == true){
                        dataManager.extendDatabase('02')}
                    if (allier.checked == true){
                        dataManager.extendDatabase('03')}
                    if (alpesdehauteprovence.checked == true){
                        dataManager.extendDatabase('04')}
                    if (hautesalpes.checked == true){
                        dataManager.extendDatabase('05')}
                    if (alpesmaritimes.checked == true){
                        dataManager.extendDatabase('06')}
                    if (ardeche.checked == true){
                        dataManager.extendDatabase('07')}
                    if (ardennes.checked == true){
                        dataManager.extendDatabase('08')}
                    if (ariege.checked == true){
                        dataManager.extendDatabase('09')}
                    if (aube.checked == true){
                        dataManager.extendDatabase('10')}
                    if (aude.checked == true){
                        dataManager.extendDatabase('11')}
                    if (aveyron.checked == true){
                        dataManager.extendDatabase('12')}
                    if (bouchesdurhone.checked == true){
                        dataManager.extendDatabase('13')}
                    if (calvados.checked == true){
                        dataManager.extendDatabase('14')}
                    if (cantal.checked == true){
                        dataManager.extendDatabase('15')}
                    if (charente.checked == true){
                        dataManager.extendDatabase('16')}
                    if (charenteMaritime.checked == true){
                        dataManager.extendDatabase('17')}
                    if (cher.checked == true){
                        dataManager.extendDatabase('18')}
                    if (corrèze.checked == true){
                        dataManager.extendDatabase('19')}
                    if (deuxBHauteCorse.checked == true){
                        dataManager.extendDatabase('2b')}
                    if (deuxACorsedusud.checked == true){
                        dataManager.extendDatabase('2a')}
                    if (côtedOr.checked == true){
                        dataManager.extendDatabase('21')}
                    if (côtesdArmor.checked == true){
                        dataManager.extendDatabase('22')}
                    if (creuse.checked == true){
                        dataManager.extendDatabase('23')}
                    if (dordogne.checked == true){
                        dataManager.extendDatabase('24')}
                    if (doubs.checked == true){
                        dataManager.extendDatabase('25')}
                    if (drôme.checked == true){
                        dataManager.extendDatabase('26')}
                    if (eure.checked == true){
                        dataManager.extendDatabase('27')}
                    if (eureetLoir.checked == true){
                        dataManager.extendDatabase('28')}
                    if (finistère.checked == true){
                        dataManager.extendDatabase('29')}
                    if (gard.checked == true){
                        dataManager.extendDatabase('30')}
                    if (hautegaronne.checked == true){
                        dataManager.extendDatabase('31')}
                    if (gers.checked == true){
                        dataManager.extendDatabase('32')}
                    if (gironde.checked == true){
                        dataManager.extendDatabase('33')}
                    if (hérault.checked == true){
                        dataManager.extendDatabase('34')}
                    if (illeetVilaine.checked == true){
                        dataManager.extendDatabase('35')}
                    if (indre.checked == true){
                        dataManager.extendDatabase('36')}
                    if (indreetLoire.checked == true){
                        dataManager.extendDatabase('37')}
                    if (isère.checked == true){
                        dataManager.extendDatabase('38')}
                    if (jura.checked == true){
                        dataManager.extendDatabase('39')}
                    if (landes.checked == true){
                        dataManager.extendDatabase('40')}
                    if (loiretCher.checked == true){
                        dataManager.extendDatabase('41')}
                    if (loire.checked == true){
                        dataManager.extendDatabase('42')}
                    if (hauteLoire.checked == true){
                        dataManager.extendDatabase('43')}
                    if (loireAtlantique.checked == true){
                        dataManager.extendDatabase('44')}
                    if (loiret.checked == true){
                        dataManager.extendDatabase('45')}
                    if (lot.checked == true){
                        dataManager.extendDatabase('46')}
                    if (lotetGaronne.checked == true){
                        dataManager.extendDatabase('47')}
                    if (lozère.checked == true){
                        dataManager.extendDatabase('48')}
                    if (maineetLoire.checked == true){
                        dataManager.extendDatabase('49')}
                    if (manche.checked == true){
                        dataManager.extendDatabase('50')}
                    if (marne.checked == true){
                        dataManager.extendDatabase('51')}
                    if (hauteMarne.checked == true){
                        dataManager.extendDatabase('52')}
                    if (mayenne.checked == true){
                        dataManager.extendDatabase('53')}
                    if (meurtheetMoselle.checked == true){
                        dataManager.extendDatabase('54')}
                    if (meuse.checked == true){
                        dataManager.extendDatabase('55')}
                    if (morbihan.checked == true){
                        dataManager.extendDatabase('56')}
                    if (moselle.checked == true){
                        dataManager.extendDatabase('57')}
                    if (nièvre.checked == true){
                        dataManager.extendDatabase('58')}
                    if (nord.checked == true){
                        dataManager.extendDatabase('59')}
                    if (oise.checked == true){
                        dataManager.extendDatabase('60')}
                    if (orne.checked == true){
                        dataManager.extendDatabase('61')}
                    if (pasdeCalais.checked == true){
                        dataManager.extendDatabase('62')}
                    if (puydeDôme.checked == true){
                        dataManager.extendDatabase('63')}
                    if (pyrénéesAtlantiques.checked == true){
                        dataManager.extendDatabase('64')}
                    if (hautesPyrénées.checked == true){
                        dataManager.extendDatabase('65')}
                    if (pyrénéesOrientales.checked == true){
                        dataManager.extendDatabase('66')}
                    if (basRhin.checked == true){
                        dataManager.extendDatabase('67')}
                    if (hautRhin.checked == true){
                        dataManager.extendDatabase('68')}
                    if (rhône.checked == true){
                        dataManager.extendDatabase('69')}
                    if (hauteSaône.checked == true){
                        dataManager.extendDatabase('70')}
                    if (saôneetLoire.checked == true){
                        dataManager.extendDatabase('71')}
                    if (sarthe.checked == true){
                        dataManager.extendDatabase('72')}
                    if (savoie.checked == true){
                        dataManager.extendDatabase('73')}
                    if (hauteSavoie.checked == true){
                        dataManager.extendDatabase('74')}
                    if (paris.checked == true){
                        dataManager.extendDatabase('75')}
                    if (seineMaritime.checked == true){
                        dataManager.extendDatabase('76')}
                    if (seineetMarne.checked == true){
                        dataManager.extendDatabase('77')}
                    if (yvelines.checked == true){
                        dataManager.extendDatabase('78')}
                    if (deuxSèvres.checked == true){
                        dataManager.extendDatabase('79')}
                    if (somme.checked == true){
                        dataManager.extendDatabase('80')}
                    if (tarn.checked == true){
                        dataManager.extendDatabase('81')}
                    if (tarnetGaronne.checked == true){
                        dataManager.extendDatabase('82')}
                    if (varr.checked == true){
                        dataManager.extendDatabase('83')}
                    if (vaucluse.checked == true){
                        dataManager.extendDatabase('84')}
                    if (vendée.checked == true){
                        dataManager.extendDatabase('85')}
                    if (vienne.checked == true){
                        dataManager.extendDatabase('86')}
                    if (hauteVienne.checked == true){
                        dataManager.extendDatabase('87')}
                    if (vosges.checked == true){
                        dataManager.extendDatabase('88')}
                    if (yonne.checked == true){
                        dataManager.extendDatabase('89')}
                    if (territoiredeBelfort.checked == true){
                        dataManager.extendDatabase('90')}
                    if (essonne.checked == true){
                        dataManager.extendDatabase('91')}
                    if (hautsdeSeine.checked == true){
                        dataManager.extendDatabase('92')}
                    if (seinesaintdenis.checked == true){
                        dataManager.extendDatabase('93')}
                    if (valdeMarne.checked == true){
                        dataManager.extendDatabase('94')}
                    if (valdOise.checked == true){
                        dataManager.extendDatabase('95')}
                }
            }




        }





    }




    //Rectangle where the map will appear
    Rectangle {
        id: mapContainer
        width: parent.width
        height: parent.height
        border.width: 0
        border.color: "#36e855"
        anchors.right: parent.right
        anchors.top: parent.top
        WebEngineView{
            id:webengine
            //                        anchors.left:mapContainer.left
            //                        anchors.right:mapContainer.right
            anchors.fill:mapContainer
            url:"file://"+path+"/card.html"
            //url:"D:/Documents/ENIB/Semestre6/CPO/0-Projet/projets6/routing/Data/card.html"            //Leo
            //url:"/home/quentin/Documents/dev/projets6/routing/Data/card.html"            //Quentin

        }

    }

    Rectangle{
        id:meteoContainer
        x:35
        y:35
        width: 350
        height: 200
        color: "#243665"
        opacity: 0
        radius : 20
        Rectangle {
            id : hideButtoncontainer
            width: 130
            height : 25
            x :(meteoContainer.width/2 - hideButton.width/2)
            y : -hideButton.height -5
            radius : 5
            color: "#243665"

            Text {
                id: desaffichermeteo
                x: 2
                y: 2
                width: 105
                height: 25
                text: "Enlever météo"
                color: "white"
            }
            Image {
                id: upArrow
                source: "qrc:/Images/move-to-next.png"
                x : 105
                y : 0
                rotation: 270
                width: 25
                height: 25
                fillMode: Image.PreserveAspectFit


            }
        }

        Button{
            id: hideButton
            width: 130
            height : 25
            x :(meteoContainer.width/2 - hideButton.width/2)
            y : -hideButton.height - 5
            opacity: 0


            /*Rectangle{
                radius : 10
                color:"#243665"
                opacity: 0.9
            }*/

            onClicked:{
                animationOFFopacity.running = true;
                animationOFFx.running = true;
                animationOFFopacity2.running = true;

            }
        }
        WeatherAddon{
            id:element
        }
        PropertyAnimation {
            id: animationOFFx;
            target: meteoContainer;
            property: "y";
            to: 35;
            duration: 400
        }
        PropertyAnimation{
            id : animationOFFopacity
            target: meteoContainer
            property: "opacity"
            to : 0
            duration: 200
        }
    }


    Rectangle {
        id: rectangleparameter
        x: 35
        y: 35
        width: 350
        height: 350
        color: "#243665"
        opacity: 0.9
        radius : 20

        PropertyAnimation{
            id : animationOFFopacity2
            target: showButtoncontainer
            property: "opacity"
            to : 1
            duration: 200
        }

        PropertyAnimation{
            id : animationONopacity2
            target: showButtoncontainer
            property: "opacity"
            to : 0
            duration: 200
        }

        Rectangle {
            id : showButtoncontainer
            width: 75
            height : 25
            x :(rectangleparameter.width/2 - showButton.width/2)
            y : rectangleparameter.height + 5
            radius : 5
            color: "#243665"

            Text {
                id: affichermeteo
                x: 2
                y: 2
                width: 50
                height: 25
                text: "météo"
                color: "white"
            }
            Image {
                id: downArrow
                source: "qrc:/Images/move-to-next.png"
                x : 50
                y : 0
                rotation: 90
                width: 25
                height: 25
                fillMode: Image.PreserveAspectFit


            }
        }


        Button{
            id: showButton
            width: 75
            height : 25
            x :(rectangleparameter.width/2 - showButton.width/2)
            y : rectangleparameter.height + 5
            opacity : 0
            onClicked:{
                animationONopacity.running = true;
                animationONx.running = true;
                animationONopacity2.running = true;
            }
        }

        PropertyAnimation {
            id: animationONx;
            target: meteoContainer;
            property: "y";
            to: 550;
            duration: 400
        }
        PropertyAnimation{
            id : animationONopacity
            target: meteoContainer
            property: "opacity"
            to : 0.9
            duration: 400
        }

        //Button to validate
        Button {
            id: valider
            x: 215
            y: 301
            width: 120
            height: 25
            opacity: 1
            layer.enabled: true
            background: Rectangle{
                radius : 20
                color : "black"
                opacity: 0.2
            }
            onClicked: {
                var startingCoordinates = myAdress.toCoordinates(enterDepartInput.text);
                var finishCoordinates = myAdress.toCoordinates(enterArriveeInput.text);

                var startCoordinate = QtPositioning.coordinate(startingCoordinates[0],startingCoordinates[1]);
                var endCoordinate = QtPositioning.coordinate(finishCoordinates[0],finishCoordinates[1]);

                if (startCoordinate.isValid && endCoordinate.isValid) {
                    var nodes = dataManager.createItinerary(startingCoordinates,finishCoordinates,kmDesired.text);
                    maCarte.sendNodes(nodes,dataManager);
                    maCarte.createMap();
                    console.log("Carte créée");
                    webengine.reload();
                    //weather.createForecast(startingCoordinates[0],startingCoordinates[1]);
                    //if(!weather.getError()){
                    //     testWeather.visible = false;
                    //   weatherIcon.source = weather.getActiveIcon();
                    // weatherDescription.text = weather.getActiveDescription();
                    //windSpeed.text = weather.getActiveWindSpeed();
                    //windIcon.source = weather.getActiveWindStrength();
                    //windIcon.rotation = weather.getActiveDirection();
                    //weatherItem.visible = true;
                    //windItem.visible = true;
                    //box.visible = true;
                    //errorItem.visible = false
                    //}
                    // else{
                    //  errorDescription.text = weather.getError();
                    //   weatherItem.visible = false;
                    //   windItem.visible = false;
                    // box.visible = false;
                    //errorItem.visible = true;
                    //testWeather.visible = true;
                    //}

                }

            }
            //zone texte
            Text {
                id: textvalider
                x: 0
                y: 0
                width: 119
                height: 24
                text: "Valider"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 15
                font.family: comfortaalight.name
                color:"white"
            }
        }

        RowLayout {
            x: 35
            y: 124
            width: 280
            height: 164

            spacing : 7

            ColumnLayout{
                spacing: 25


                //icons

                Image {
                    id: imageDeparture
                    y: 9
                    width: parent.width
                    height: parent.height
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/Images/logovert.png"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 10
                    Layout.preferredHeight: 10
                    Layout.alignment: Qt.AlignCenter
                }

                Image {
                    id: imageArrival
                    y: 68
                    width: parent.width
                    height: parent.height
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/Images/logorouge.png"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 10
                    Layout.preferredHeight: 10
                    Layout.alignment: Qt.AlignCenter
                }


                Image {
                    id: imageRoad
                    y: 129
                    width: parent.width
                    height: parent.height
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/Images/road.png"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 10
                    Layout.preferredHeight: 10
                    Layout.alignment: Qt.AlignCenter
                }

            }


            ColumnLayout{
                x: 396
                y: 377
                spacing: 5

                //route settings


                TextField {
                    id: enterDepartInput
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 30
                    Layout.preferredHeight: 20
                    Layout.alignment: Qt.AlignCenter
                    font.pixelSize: 20
                    color:"#ffffff"
                    placeholderText : "Départ"
                    horizontalAlignment: Text.AlignLeft
                    font.family: comfortaalight.name
                    background : Rectangle {
                        opacity: 0
                    }


                    Rectangle {
                        id: rectangle1
                        x: 0
                        y: 46
                        width: 208
                        height: 3
                        color: "#8bd8bd"
                    }


                }
                TextField {
                    id: enterArriveeInput
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 30
                    Layout.preferredHeight: 20
                    Layout.alignment: Qt.AlignCenter
                    font.pixelSize: 20
                    color:"#ffffff"
                    placeholderText : "Arrivée"
                    horizontalAlignment: Text.AlignLeft
                    font.family: comfortaalight.name
                    background : Rectangle {
                        opacity: 0
                    }

                    Rectangle {
                        id: rectangle
                        x: 0
                        y: 47
                        width: 208
                        height: 3
                        color: "#8bd8bd"
                    }
                }
                TextField {
                    id: kmDesired
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 30
                    Layout.preferredHeight: 20
                    Layout.alignment: Qt.AlignCenter
                    font.pixelSize: 20
                    color:"#ffffff"
                    placeholderText : "0 km"
                    font.capitalization: Font.MixedCase
                    font.underline: false
                    visible: true
                    font.family: comfortaalight.name
                    horizontalAlignment: Text.AlignLeft
                    background : Rectangle {
                        opacity: 0
                    }

                    Rectangle {
                        id: rectangle2
                        x: 0
                        y: 48
                        width: 208
                        height: 3
                        color: "#8bd8bd"
                    }
                }
            }
        }

        RowLayout {
            x: 35
            y: 35
            width: 280
            height: 70
            spacing: 5
            opacity: 0.9

            Image {
                id: logopetit
                width: 70
                height: 70
                fillMode: Image.PreserveAspectFit
                source: "qrc:/Images/logogrand.png"
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: 70
                Layout.preferredHeight: 70
                Layout.alignment: Qt.AlignCenter
            }

            Text {
                id: nom
                height: 70
                text: "BIKEN"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 70
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignCenter
                color: "#8bd8bd"
                font.family: comfortaalight.name
            }
        }


    }

}



















/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

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
    ListModel {
        id :listdpt
    }

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
        x: 100
        y: 100
        width: 900
        height: 300
        Column {
            CheckBox {
                id : ain01
                text : "Ain"
            }
            CheckBox {
                id : aisne02
                text : "Aisne"
            }
            CheckBox {
                id : allier03
                text : "Allier"
            }
            CheckBox {
                id : alpesdehauteprovence04
                text : "Alpes-de-Haute-Provence"
            }
            CheckBox {
                id : hatesalpes05
                text : "Hautes-Alpes"
            }
            CheckBox {
                id : alpesmaritimes06
                text : "Alpes-Maritimes"
            }
            CheckBox {
                id : ardeche07
                text : "Ardèche"
            }
            CheckBox {
                id : ardennes08
                text : "Ardennes"
            }
            CheckBox {
                id : ariege09
                text : "Ariège"
            }
            CheckBox {
                id : aube10
                text : "Aube"
            }
            CheckBox {
                id : aude11
                text : "Aude"
            }
            CheckBox {
                id : aveyron12
                text : "Aveyron"
            }
            CheckBox {
                id : bouchesdurhone13
                text : "Bouches-du-Rhône"
            }
            CheckBox {
                id : calvados14
                text : "Calvados"
            }
            Button {
                id : refreshDatabase
                onClicked : {
                    if (ain01.checked == true){
                        listdpt.append({'number':'01'})
                        dataManager.extendDatabase("01")
                    }
                }




            }




            //                Cantal
            //                Charente
            //                Charente-Maritime
            //                Cher
            //                Corrèze
            //                Côte-d Or
            //                Côtes-d Armor
            //                Creuse
            //                Dordogne
            //                Doubs
            //                Drôme
            //                Eure
            //                Eure-et-Loir
            //                Finistère
            //                2ACorse-du-Sud
            //                2BHaute-Corse
            //                Gard
            //                Haute-Garonne
            //                Gers
            //                Gironde

            //                Hérault
            //                Ille-et-Vilaine
            //                Indre
            //                Indre-et-Loire
            //                Isère
            //                Jura
            //                Landes
            //                Loir-et-Cher
            //                Loire
            //                Haute-Loire
            //                Loire-Atlantique
            //                Loiret
            //                Lot
            //                Lot-et-Garonne
            //                Lozère
            //                Maine-et-Loire
            //                Manche
            //                Marne
            //                Haute-Marne
            //                Mayenne
            //                Meurthe-et-Moselle
            //                Meuse
            //                Morbihan
            //                Moselle
            //                Nièvre
            //                Nord
            //                Oise
            //                Orne
            //                Pas-de-Calais
            //                Puy-de-Dôme
            //                Pyrénées-Atlantiques
            //                Hautes-Pyrénées
            //                Pyrénées-Orientales
            //                Bas-Rhin

            //                Haut-Rhin
            //                Rhône
            //                Haute-Saône
            //                Saône-et-Loire
            //                Sarthe
            //                Savoie
            //                Haute-Savoie
            //                Paris
            //                Seine-Maritime
            //                Seine-et-Marne
            //                Yvelines
            //                Deux-Sèvres
            //                Somme
            //                Tarn
            //                Tarn-et-Garonne
            //                Var
            //                Vaucluse
            //                Vendée
            //                Vienne
            //                Haute-Vienne
            //                Vosges
            //                Yonne
            //                Territoire de Belfort
            //                Essonne
            //                Hauts-de-Seine
            //                Seine-Saint-Denis
            //                Val-de-Marne
            //                Val-d Oise
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
                    weather.createForecast(startingCoordinates[0],startingCoordinates[1]);
                    if(!weather.getError()){
                        testWeather.visible = false;
                        weatherIcon.source = weather.getActiveIcon();
                        weatherDescription.text = weather.getActiveDescription();
                        windSpeed.text = weather.getActiveWindSpeed();
                        windIcon.source = weather.getActiveWindStrength();
                        windIcon.rotation = weather.getActiveDirection();
                        weatherItem.visible = true;
                        windItem.visible = true;
                        box.visible = true;
                        errorItem.visible = false
                    }
                    else{
                        errorDescription.text = weather.getError();
                        weatherItem.visible = false;
                        windItem.visible = false;
                        box.visible = false;
                        errorItem.visible = true;
                        testWeather.visible = true;
                    }

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

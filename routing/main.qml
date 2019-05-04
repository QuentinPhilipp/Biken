import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtLocation 5.6
import QtPositioning 5.6
import "helper.js" as Helper
import"map"
import QtWebEngine 1.7

/*
  Coodrinates for the test:
  48.368718
  -4.588330

  48.535807
  -4.658547
*/

ApplicationWindow {
    id: mainWaindow

    property var map

    width: 1500
    minimumWidth: 800
    height: 800
    minimumHeight: 400
    visible: true

    //Rectangle where the map will appear
    Rectangle{
        id: mapContainer
        width: 0.8*parent.width
        height: 0.7*parent.height
        anchors.right: parent.right
        anchors.top: parent.top
        color: "green"
        WebEngineView{
            anchors.left:mapContainer.left
            anchors.right:mapContainer.right
            anchors.fill:mapContainer
            url: "file:///home/beuzet/Documents/projets6/routing/maCartecolor.html"
                     }

            }
    menuBar: MenuBar { 
        Menu {
            title: "Fichier"
            MenuItem { text: "Open" }
            MenuItem { text: "Close" }
        }

        Menu {
            title: "Paramètres"
        }
        Menu {
            title: "Export"
        }
        Menu {
            title: "Credit"
        }
    }

    //Rectangle where every parameter for the route can be set (position, distance...)

    Rectangle{
        id: paramContainer
        width: 0.2*parent.width
        height: 0.7*parent.height
        anchors.right: mapContainer.left
        anchors.top: parent.top
        color: "#8bd8bd"
        border.color: "blue"
        /*
        //Recherche avec des coordonnées
        Text {
            id: fromCoordinateText
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 20
            text: qsTr("Depart")
            font.pixelSize: 12
            color:"white"
        }
        Rectangle{
            id: fromLatitude
            anchors.left: fromCoordinateText.right
            anchors.leftMargin: 10
            anchors.top: fromCoordinateText.top
            width: 95
            height: 20
            color: "black"
            TextInput{
                id: fromLatitudeInput
                anchors.fill:parent
                font.pixelSize: 12
                color:"white"
            }
        }
        Rectangle{
            id: fromLongitude
            anchors.left: fromLatitude.right
            anchors.leftMargin: 10
            anchors.top: fromCoordinateText.top
            width: 95
            height: 20
            color: "black"
            TextInput{
                id: fromLongitudeInput
                anchors.fill:parent
                font.pixelSize: 12
                color:"white"
            }
        }

        Text {
            id: toCoordinateText
            anchors.left: fromCoordinateText.left
            anchors.top: fromCoordinateText.top
            anchors.topMargin: 30
            text: qsTr("Arrivee")
            font.pixelSize: 12
            color:"white"
        }

        Rectangle{
            id: toLatitude
            anchors.left: fromLatitude.left
            anchors.top: fromLatitude.bottom
            anchors.topMargin: 10
            width: 95
            height: 20
            color: "black"
            TextInput{
                id: toLatitudeInput
                anchors.fill:parent
                font.pixelSize: 12
                color:"white"
            }
        }
        Rectangle{
            id: toLongitude
            anchors.left: fromLongitude.left
            anchors.top: fromLongitude.bottom
            anchors.topMargin: 10
            width: 95
            height: 20
            color: "white"
            TextInput{
                id: toLongitudeInput
                anchors.fill:parent
                font.pixelSize: 12
                color:"black"
            }
        }

        Button{
            id: validationCoordinate
            anchors.left: parent.left
            anchors.right: toLongitude.right
            anchors.top: toLongitude.bottom
            anchors.topMargin: 10
            width: 20
            height: 20
            onClicked: {
                var startCoordinate = QtPositioning.coordinate(parseFloat(fromLatitudeInput.text),
                                                               parseFloat(fromLongitudeInput.text));
                var endCoordinate = QtPositioning.coordinate(parseFloat(toLatitudeInput.text),
                                                             parseFloat(toLongitudeInput.text));

                if (startCoordinate.isValid && endCoordinate.isValid) {
                    thisIsTheMap.calculateCoordinateRoute(startCoordinate,endCoordinate)
                }
            }
            Text{
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 2
                font.pixelSize: 12
                text: "Valider"
                color: "black"
            }
        }
        */

        //Recherche avec une adresse
        Text {
            id: fromAdressText
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: validationCoordinate.bottom
            anchors.topMargin: 20
            text: qsTr("Depart")
            font.pixelSize: 12
            color:"black"
        }
        Rectangle{
            id: fromAdress
            anchors.left: fromAdressText.right
            anchors.leftMargin: 25
            anchors.top: fromAdressText.top
            anchors.right: mapContainer.left
            width: 0.6*parent.width
            height: 20
            color: "white"
            TextInput{
                id: fromAdressInput
                anchors.fill:parent
                font.pixelSize: 12
                color:"black"
            }
        }
        Text {
            id: toAdressText
            anchors.left: fromAdressText.left
            anchors.top: fromAdressText.top
            anchors.topMargin: 30
            text: qsTr("Arrivee")
            font.pixelSize: 12
            color:"black"
        }
        Rectangle{
            id: toAdress
            anchors.left: fromAdress.left
            anchors.top: fromAdress.bottom
            anchors.topMargin: 10
            width: 0.6*parent.width
            height: 20
            color: "white"
            TextInput{
                id: toAdressInput
                anchors.fill:parent
                font.pixelSize: 12
                color:"black"
            }
        }

        //Recherche avec un nombre précis de kilomètres
        Text {
            id: kmDesiredText
            anchors.left: fromAdressText.left
            anchors.top: fromAdressText.top
            anchors.topMargin: 60
            text: qsTr("km désirés")
            font.pixelSize: 12
            color:"black"
        }
        Rectangle{
            id: kmDesired
            anchors.left: fromAdress.left
            anchors.top: fromAdress.bottom
            anchors.topMargin: 40
            width: 0.6*parent.width
            height: 20
            color: "white"
            TextInput{
                id: kmDesiredInput
                font.pixelSize: 12
                anchors.fill:parent
                color:"black"
            }
        }

        Button{
            id: validationAdress
            anchors.right: toAdress.right
            anchors.top: toAdress.bottom
            anchors.topMargin: 40
            width: 70
            height: 20
            onClicked: {
                var startingCoordinates = myAdress.toCoordinates(fromAdressInput.text);
                var finishCoordinates = myAdress.toCoordinates(toAdressInput.text);

                var startCoordinate = QtPositioning.coordinate(startingCoordinates[0],startingCoordinates[1]);
                var endCoordinate = QtPositioning.coordinate(finishCoordinates[0],finishCoordinates[1]);

                if (startCoordinate.isValid && endCoordinate.isValid) {
                    thisIsTheMap.calculateCoordinateRoute(startCoordinate,endCoordinate)
                }
            }
            Text{
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 2
                font.pixelSize: 12
                text: "Valider"
                color: "black"
            }
        }

        //Test: create a route in the C++ files, receive it here and then show it on the map
        Button{
            id: testButton
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: validationAdress.bottom
            anchors.topMargin: 20
            width: 150
            height: 20
            onClicked: {
                //Calls the function findRouteFrom(lat,lon) from datamanager in C++. It will return a list of nodes which are
                //themself a list of 2 coordinates (latitude,longitude). Those nodes represent every node on which you change
                //from one road to another.
                console.log("Calculating route...");
                var nodes = dataManager.findRouteFrom(4.5,5.6); //(random parameters, they are not used yet)
                console.log("Data received in QML");
                //Then calculate a route that goes through every of those nodes
                thisIsTheMap.setNodes(nodes);
                thisIsTheMap.calculateCoordinateRouteWithNodes();
            }
            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 2
                font.pixelSize: 12
                text: "TEST"
                color: "black"
            }
        }
        Rectangle{
            width: 0.95*parent.width
            height: 0.4*parent.height
            anchors.left: fromAdressText.left
            anchors.top: testButton.bottom
            anchors.right: mapContainer.left
            anchors.topMargin: 10
            color:"#243665"
            border.color: "blue"
            ScrollView{
                id: view
                anchors.fill: parent
                TextArea{
                    id: textToDisplay
                    width: 0.95*parent.width
                    height: 0.4*parent.height
                    anchors.fill: parent
                    font.pixelSize: 12
                    color:"white"
                }
            }
        }
     }

    //Rectangle where we will display meteo information
    Rectangle{
        id: meteoContainer
        width: 0.2*parent.width
        height: 0.3*parent.height
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        color: "#2525ff"
        border.color: "blue"
        opacity: 0.2
    }

    //Another rectangle, don't know what we will put in it yet
    Rectangle{
        id: overviewContainer
        width: 0.8*parent.width
        height: 0.3*parent.height
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "#8bd8bd"
        border.color: "blue"
        Rectangle{
            anchors.right: setRadius.left
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            width: 50
            height: 30
            color: "#8bd8bd"
            Text{
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 14
                color:"black"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text:"Radius (in km):"
            }
        }
        Rectangle{
            id:setRadius
            anchors.right: refreshDataBase.left
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            width: 50
            height: 30
            color: "white"
            TextInput{
                id: radius
                anchors.fill:parent
                font.pixelSize: 14
                color:"black"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
        Button{
            id: refreshDataBase
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            width:120
            height:40
            onClicked: {
                if(radius.length!=0){
                    var radiusValue = radius.text*1000;
                    console.log(radiusValue);
                    if(radiusValue<=50000 && radiusValue>=200){
                        displayInfos.color = "white"
                        displayInfos.text = "Refreshing ..."
                        dataManager.generateWaysAndNodes(radiusValue);
                        displayInfos.text = "Done."
                    }
                    else{
                        displayInfos.color = "#EB6A63";
                        displayInfos.text = "Error: Radius must be between 1km and 50km"
                    }
                }
            }
            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 13
                text: "Refresh database"
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: "black"
            }
        }
        Text{
            id:displayInfos
            anchors.top: setRadius.bottom
            anchors.topMargin: 35
            anchors.horizontalCenter: setRadius.horizontalCenter
            font.pixelSize: 12
            color:"white"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text:""
            }
        }
    }


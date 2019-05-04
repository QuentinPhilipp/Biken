import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtLocation 5.6
import QtPositioning 5.6
import "helper.js" as Helper
import "map"

ApplicationWindow {
    id: mainWaindow

    property var map

    width: 1500
    minimumWidth: 1000
    height: 800
    color: "#adb9c8"
    minimumHeight: 400
    visible: true

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

    //background
    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        border.width: 2
        border.color: "#36e855"
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#30a8f4"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }

        //Rectangle where the map will appear
        Rectangle {
            id: mapContainer
                    width: 0.73*parent.width
                    height: parent.height
                    border.width: 2
                    border.color: "#36e855"
                    anchors.right: parent.right
                    anchors.top: parent.top
                    Plugin {                                //A Plugin has to be set to create a map
                        id: mapPlugin
                        preferred: ["osm", "esri"]
                    }
                    MyMap {                                 //permet de créer un object MyMap (défini dans le fichier "MyMap.qml")
                        id : thisIsTheMap
                        anchors.fill: mapContainer
                        plugin: mapPlugin


                        //refresh the database
                        Rectangle {
                            id: inputRadius
                            anchors.left : textRadius.right
                            y: 20
                            width: 50
                            height: 25
                            color: "#ffffff"
                            border.width: 2
                            border.color: "#36e855"
                            TextInput{
                                id: radius
                                anchors.fill:parent
                                font.pixelSize: 15
                                color:"black"
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }

                        }

                        Rectangle {
                            id: textRadius
                            anchors.left : mapContainer.left
                            width: 105
                            height: 25
                            y: 20
                            color: "#ffffff"
                            border.width: 2
                            border.color: "#36e855"
                            //zone texte
                            Text {
                                id: texttextRadius
                                x: 6
                                y: 4
                                text: qsTr("Radius in km :")
                                font.pixelSize: 15
                                color:"black"
                            }
                        }

                        //Another rectangle, don't know what we will put in it yet
                        Button{
                            y: 12.5
                            id: refreshDataBase
                            anchors.left: inputRadius.right
                            width:152
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
                                font.pixelSize: 15
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
                            font.pixelSize: 15
                            color:"white"
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            text:""
                            }
                        }
                    }
            }

        //Rectangle with the inscription "Départ"
        Rectangle {
            id: textDepart
            x: 10
            y: 10
            width: 91
            height: 25
            color: "#ffffff"
            border.width: 2
            border.color: "#36e855"

            //zone texte
            Text {
                id: texttextDepart
                x: 23
                y: 0
                width: 61
                height: 25
                text: qsTr("Départ")
                font.pixelSize: 15
                color:"black"
            }

        }

        //Rectangle where the user indicates the departure
        Rectangle {
            id: enterDepart
            x: 117
            y: 10
            width: 0.14*parent.width
            height: 25
            color: "#ffffff"
            border.width: 2
            border.color: "#36e855"

            TextInput{
                id: enterDepartInput
                anchors.fill: parent
                font.pixelSize: 15
                color:"black"
            }

        }

        //Rectangle with the inscription "Arrivée"
        Rectangle {
            id: textArrivee
            x: 10
            y: 50
            width: 91
            height: 25
            color: "#ffffff"
            border.width: 2
            border.color: "#36e855"
            //zone texte

            Text {
                id: texttextArrivee
                x: 23
                y: 0
                width: 60
                height: 25
                text: qsTr("Arrivée")
                font.pixelSize: 15
                color:"black"
            }
        }

        //Rectangle where the user indicates the arrival
        Rectangle {
            id: enterArrivee
            x: 117
            y: 50
            width: 0.14*parent.width
            height: 25
            color: "#ffffff"
            border.width: 2
            border.color: "#36e855"
            TextInput{
                id: enterArriveeInput
                anchors.fill: parent
                font.pixelSize: 15
                color:"black"
            }
        }

        //Rectangle with the inscription "km désirés"
        Rectangle {
            id: textkmDesired
            x: 10
            y: 90
            width: 91
            height: 25
            color: "#ffffff"
            border.width: 2
            border.color: "#36e855"

            //zone texte
            Text {
                id: texttextkmDesired
                x: 8
                y: 0
                width: 75
                height: 25
                text: qsTr("km désirés")
                font.pixelSize: 15
                color:"black"
            }
        }

        //Rectangle where the user indicates the number of km
        Rectangle {
            id: enterkmDesired
            x: 116
            y: 90
            width: 0.14*parent.width
            height: 25
            color: "#ffffff"
            border.width: 2
            border.color: "#36e855"
            TextInput{
                id: enterkmDesiredInput
                anchors.fill: parent
                font.pixelSize: 15
                color:"black"
            }
        }

        //Button to validate
        Button {
            id: valider
            x: 10
            y: 134
            width: 100
            height: 25
            onClicked: {
                            var startingCoordinates = myAdress.toCoordinates(enterDepartInput.text);
                            var finishCoordinates = myAdress.toCoordinates(enterArriveeInput.text);

                            var startCoordinate = QtPositioning.coordinate(startingCoordinates[0],startingCoordinates[1]);
                            var endCoordinate = QtPositioning.coordinate(finishCoordinates[0],finishCoordinates[1]);

                            if (startCoordinate.isValid && endCoordinate.isValid) {
                                thisIsTheMap.calculateCoordinateRoute(startCoordinate,endCoordinate)
                            }
                        }
            //zone texte
            Text {
                id: textvalider
                x: 29
                y: 0
                width: 71
                height: 25
                text: qsTr("Valider")
                font.pixelSize: 15
                color:"black"
            }

        }

        //Rectangle to display the details of the way
        Rectangle {
            id: chemin
            x: 10
            y: 176
            width: 0.25*parent.width
            height: 0.25*parent.height
            color: "#ffffff"
            border.width: 2
            border.color: "#36e855"
            ScrollView{
                id: view
                anchors.fill: parent
                TextArea{
                    anchors.fill: parent
                    id: textToDisplay
                    font.pixelSize: 15
                    color:"black"
                }
            }

        }
    }







import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtLocation 5.6
import QtPositioning 5.6
import "helper.js" as Helper
import "map"
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4


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
        x: 100
        y: 100
        width: 900
        height: 300

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
        Plugin {                                //A Plugin has to be set to create a map
            id: mapPlugin
            preferred: ["osm", "esri"]
        }
        MyMap {                                 //permet de créer un object MyMap (défini dans le fichier "MyMap.qml")
            id : thisIsTheMap
            anchors.fill: mapContainer
            plugin: mapPlugin
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

//            layer.effect: DropShadow {
//                transparentBorder: true
//                horizontalOffset: 3
//                verticalOffset: 3
//            }
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

            spacing : 2

            ColumnLayout{
                spacing: 5


                //icons

                Image {
                    id: imageDeparture
                    width: parent.width
                    height: parent.height
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/Images/placeholder.png"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 10
                    Layout.preferredHeight: 20
                    Layout.alignment: Qt.AlignCenter
                }

                Image {
                    id: imageArrival
                    width: parent.width
                    height: parent.height
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/Images/flag.png"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 10
                    Layout.preferredHeight: 20
                    Layout.alignment: Qt.AlignCenter
                }


                Image {
                    id: imageRoad
                    width: parent.width
                    height: parent.height
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/Images/road.png"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 10
                    Layout.preferredHeight: 20
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
                    text: "Départ"
                    font.family: comfortaalight.name
                    horizontalAlignment: Text.AlignHCenter
                    background : Rectangle {
                        opacity: 0
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
                    text: "Arrivée"
                    horizontalAlignment: Text.AlignHCenter
                    font.family: comfortaalight.name
                    background : Rectangle {
                        opacity: 0
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
                    text: "0"
                    visible: true
                    font.family: comfortaalight.name
                    horizontalAlignment: Text.AlignHCenter
                    background : Rectangle {
                        opacity: 0
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
                //                width: 70
                //                height: 70
                //                fillMode: Image.PreserveAspectFit
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



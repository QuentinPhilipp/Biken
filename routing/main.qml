import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtLocation 5.6
import QtPositioning 5.6
import "helper.js" as Helper
import "map"
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.2
import QtWebEngine 1.7



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
            anchors.left:mapContainer.left
            anchors.right:mapContainer.right
            anchors.fill:mapContainer
//            url:"file://"+path+"/card.html"
            url:"D:/Documents/ENIB/Semestre6/CPO/0-Projet/projets6/routing/Data/card.html"
            }
      Button{
          id: testButton
          anchors.horizontalCenter: parent.horizontalCenter
          anchors.top: parent.top
          anchors.topMargin: 10
          width: 150
          height: 20
          onClicked: {
              //Calls the function findRouteFrom(lat,lon) from datamanager in C++. It will return a list of nodes which are
              //themself a list of 2 coordinates (latitude,longitude). Those nodes represent every node on which you change
              //from one road to another.
              console.log("Calculating route...");
              //var nodes = dataManager.findRouteFrom(4.5,5.6); //(random parameters, they are not used yet)
              var nodes = dataManager.findRoute(); //(random parameters, they are not used yet)

              maCarte.sendNodes(nodes,dataManager);
              console.log("Data received in QML");
               maCarte.createMap();
              console.log("Carte créée");
              webengine.reload();

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

        Rectangle {
            id: rectanglelogo
            x: 35
            y: 35
            width: 250
            height: 175
            color: "#ffffff"
            opacity: 0.7
            radius : 20

            ColumnLayout {
                x: 0
                y: 10
                width: 240
                height: 165
                spacing : 5

                Image {
                    id: imageLogoGrand
                    width: parent.width
                    height: parent.height
                    fillMode: Image.PreserveAspectFit
                    source: "logogrand.png"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1000
                    Layout.preferredHeight: 1000
                    Layout.alignment: Qt.AlignCenter
                }

                Text {
                    id: textBIKEN
                    width: 240
                    height: 30
                    text: qsTr("BIKEN")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignCenter
                    font.pixelSize: 30
                    color:"black"
                }

            }
        }

        Rectangle {
            id: rectangleparameter
            x: 35
            y: 225
            width: 250
            height: 175
            color: "#ffffff"
            opacity: 0.7
            radius : 20

            //Button to validate
            Button {
                id: valider
                x: 75
                y: 135
                width: 100
                height: 25
                opacity: 1
                layer.enabled: true
                layer.effect: DropShadow {
                    transparentBorder: true
                    horizontalOffset: 3
                    verticalOffset: 3
                }
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
                    width: 99
                    height: 24
                    text: qsTr("Valider")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 15
                    color:"black"
                }

            }






            RowLayout {
                x: 10
                y: 10
                width: 240
                height: 115

                spacing : 2

                ColumnLayout{
                    spacing: 5


                        //icons

                        Image {
                            id: imageDeparture
                            width: parent.width
                            height: parent.height
                            fillMode: Image.PreserveAspectFit
                            source: "placeholder.png"
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
                            source: "flag.png"
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
                            source: "road.png"
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
                    spacing: 10

                    //route settings



                        TextEdit {
                            id: enterDepartInput
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredWidth: 30
                            Layout.preferredHeight: 20
                            Layout.alignment: Qt.AlignCenter
                            font.pixelSize: 20
                            color:"black"
                            text: qsTr("Départ")
                            horizontalAlignment: Text.AlignHCenter

                        }

                        TextEdit {
                            id: enterArriveeInput
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredWidth: 30
                            Layout.preferredHeight: 20
                            Layout.alignment: Qt.AlignCenter
                            font.pixelSize: 20
                            color:"black"
                            text: qsTr("Arrivée")
                            horizontalAlignment: Text.AlignHCenter

                        }
                        TextEdit {
                            id: kmDesired
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredWidth: 30
                            Layout.preferredHeight: 20
                            Layout.alignment: Qt.AlignCenter
                            font.pixelSize: 20
                            color:"black"
                            text: qsTr("0")
                            horizontalAlignment: Text.AlignHCenter

                        }


                }
            }

        }
    }
}

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
        x: 100
        y: 100
        width: 900
        height: 300

    }
    MouseArea{
        width : parent.width
        height : parent.height

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
                    var nodes = dataManager.createItinerary();
                    maCarte.sendNodes(nodes,dataManager)
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

        }

        Rectangle{
            id:meteoContainer
            x:35
            y:550
            width: 350
            height: 250
            color: "#243665"
            opacity: 0.9
            radius : 20
            Button{
                id: hideButton
                width: 50
                height : 25
                x :(meteoContainer.width/2 - hideButton.width/2)
                y : -hideButton.height
                background: Rectangle{
                    radius : 10
                    color:"#243665"
                    opacity: 0.9
                }
                onClicked:{
                    if(meteoContainer.visible === true){
                        meteoContainer.visible = false;
                    }
                }
            }
            WeatherAddon{
                id:element
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

            Button{
                id: showButton
                width: 50
                height : 25
                x :(rectangleparameter.width/2 - showButton.width/2)
                y : rectangleparameter.height
                background: Rectangle{
                    radius : 10
                    color:"#243665"
                    opacity: 0.9
                }
                onClicked:{
                    if(meteoContainer.visible === false){
                        meteoContainer.visible = true;
                    }
                }
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
                    spacing: 20


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
}















/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Controls.Private 1.0

Rectangle {
    id : weatherAddon
    Rectangle{
        id : weatherRec
        anchors.top: parent.top
        anchors.left:parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.margins: 10
        color:"#f5f5f5"
        Text{
            id:weatherTitle
            anchors.top:parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Weather Forecast"
            anchors.margins: 10
        }

        ComboBox {
            anchors.top: weatherTitle.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 10
            id: box
            width: 0.8*meteoContainer.width
            visible: false

            model: ListModel{

                id: forecastItem
                ListElement{text:"Now"}
                ListElement{text:"+ 3 heures"}
                ListElement{text:"+ 6 heures"}
                ListElement{text:"+ 9 heures"}
                ListElement{text:"+ 12 heures"}
                ListElement{text:"+ 15 heures"}
                ListElement{text:"+ 18 heures"}
                ListElement{text:"+ 21 heures"}
                ListElement{text:"+ 24 heures"}
                ListElement{text:"+ 1 jour et 3 heures"}
                ListElement{text:"+ 1 jour et 06 heures"}
                ListElement{text:"+ 1 jour et 09 heures"}
                ListElement{text:"+ 1 jour et 12 heures"}
                ListElement{text:"+ 1 jour et 15 heures"}
                ListElement{text:"+ 1 jour et 18 heures"}
                ListElement{text:"+ 1 jour et 21 heures"}
                ListElement{text:"+ 2 jours"}
                ListElement{text:"+ 2 jours et 03 heures"}
                ListElement{text:"+ 2 jours et 06 heures"}
                ListElement{text:"+ 2 jours et 09 heures"}
                ListElement{text:"+ 2 jours et 12 heures"}
                ListElement{text:"+ 2 jours et 15 heures"}
                ListElement{text:"+ 2 jours et 18 heures"}
                ListElement{text:"+ 2 jours et 21 heures"}
                ListElement{text:"+ 3 jours"}
            }
            onCurrentIndexChanged: {
                if (weatherItem.visible === true){
                    weather.changeForecast(box.currentIndex);
                    weatherIcon.source = weather.getActiveIcon();
                    weatherDescription.text = weather.getActiveDescription();
                    windIcon.source = weather.getActiveWindStrength();
                    windIcon.rotation = weather.getActiveDirection();
                    windSpeed.text = weather.getActiveWindSpeed();
                }
            }
        }
        Button{
            id:testWeather
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            height: 20
            visible:true
            Text{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 2
                font.pixelSize: 12
                text: "TEST"
                color: "black"
            }
            onClicked: {
                weather.createForecast(48.4000000,-4.4833300);
                if(!weather.getError()){
                    testWeather.visible = false;
                    weatherIcon.source = weather.getActiveIcon();
                    weatherDescription.text = weather.getActiveDescription();
                    windSpeed.text = weather.getActiveWindSpeed();
                    windIcon.source = weather.getActiveWindStrength();
                    windIcon.rotation = weather.getActiveDirection();
                    weatherItem.visible = true;
                    box.visible = !box.visible;
                    errorItem.visible = false
                }
                else{
                    errorDescription.text = weather.getError();
                    errorItem.visible = true;
                    testWeather.visible = true;
                }
            }
        }
        Item{
            id:weatherItem
            visible:false
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.top:box.bottom
            Text{
                id:weatherDescription
                anchors.margins: 10
                anchors.left:weatherItem.left
                anchors.top: weatherItem.top
            }
            Image {
                id: weatherIcon
                asynchronous: true
                anchors.top: weatherDescription.bottom
                anchors.left: weatherItem.left
                anchors.margins: 10
                sourceSize.width : 0.2*meteoContainer.width
                sourceSize.height : 0.2*meteoContainer.height
                fillMode: Image.Stretch
            }

            Text{
                id:windSpeed
                anchors.margins: 10
                anchors.left:weatherDescription.right
                anchors.top: weatherItem.top
            }
            Image {
                id: windIcon
                asynchronous: true
                anchors.top: windSpeed.bottom
                anchors.left: weatherIcon.right
                anchors.margins: 10
                sourceSize.width : 0.2*meteoContainer.width
                sourceSize.height : 0.2*meteoContainer.height
                fillMode: Image.Stretch
            }
        }
        Item {
            id: errorItem
            visible: false
            anchors.horizontalCenter: weatherRec.horizontalCenter
            anchors.verticalCenter: weatherRec.verticalCenter
            Text{
                id:errorDescription
                anchors.margins: 10
                anchors.horizontalCenter: errorItem.horizontalCenter
                anchors.top: errorItem.top
            }
            Image{
                id :errorIcon
                asynchronous: true
                anchors.top: errorDescription.bottom
                anchors.horizontalCenter: errorItem.horizontalCenter
                anchors.margins:10
                sourceSize.width : 0.3*meteoContainer.width
                sourceSize.height : 0.3*meteoContainer.height
                fillMode: Image.Stretch
                source: "qrc:/icons/connexion.png"
            }
        }
    }
}

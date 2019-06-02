import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Controls.Private 1.0
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4

//This item has to be summon from a Rectangle with size parameters and id : meteoContainer
ColumnLayout {
    id : weatherAddon
    width : meteoContainer.width
    height: meteoContainer.height
    spacing: 7
    Layout.alignment: Qt.AlignCenter

    property var rotationvalue: 0

    function activate(coord1,coord2){
        weather.createForecast(coord1,coord2);
        if(!weather.getError()){
            weatherIcon.source = weather.getActiveIcon();
            weatherDescription.text = weather.getActiveDescription();
            windSpeed.text = weather.getActiveWindSpeed();
            windIcon.source = weather.getActiveWindStrength();
            windIcon.rotation = weather.getActiveDirection();
            weatherItem.visible = true;
            windItem.visible = true;
            box.visible = true;
            errorItem.visible = false;
            animationONopacity.running = true;
            animationONx.running = true;
        }
        else{
            errorDescription.text = weather.getError();
            weatherItem.visible = false;
            windItem.visible = false;
            box.visible = false;
            errorItem.visible = true;
        }
    }

    Text{
        id:weatherTitle
        font.pixelSize: 20
        color:"#ffffff"
        font.family: comfortaalight.name
        text: "Prévisions météo"
        Layout.alignment: Qt.AlignCenter
        Layout.topMargin: 5
    }

    ComboBox {
        id: box
        width: 0.8*meteoContainer.width
        visible: false
        Layout.alignment: Qt.AlignCenter
        Layout.leftMargin: 20
        Layout.rightMargin: 20
        Layout.fillWidth: true
        font.pixelSize: 20
        font.family: comfortaalight.name
        model: ListModel{

            id: forecastItem
            ListElement{text:"Maintenant"}
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
                //windIcon.rotation = weather.getActiveDirection();
                windSpeed.text = weather.getActiveWindSpeed();
                rotationvalue = weather.getActiveDirection();
                onIndexChangeRotation.running = true;
            }
        }
    }

    RowLayout{
        spacing:10
        id: layouts

        ColumnLayout{
            id:weatherItem
            visible:false
            spacing : 10
            Layout.alignment: Qt.AlignLeft
            width: layouts.width / 2
            height:meteoContainer.height - weatherItem.x
            Text{
                id:weatherDescription
                Layout.margins: 10
                Layout.fillWidth: true
                font.pixelSize: 15
                color:"#ffffff"
                font.family: comfortaalight.name
                horizontalAlignment: Text.AlignHCenter
            }
            Image {
                id: weatherIcon
                asynchronous: true
                Layout.alignment: Qt.AlignCenter
                sourceSize.width : 0.4*meteoContainer.width
                sourceSize.height : windIcon.width
            }
        }
        ColumnLayout{
            id:windItem
            visible: false
            spacing : 10
            width: layouts.width / 2
            Layout.alignment: Qt.AlignRight
            height:meteoContainer.height - windItem.x
            Text{
                id:windSpeed
                Layout.fillWidth: true
                Layout.margins: 10
                font.pixelSize: 15
                color:"#ffffff"
                font.family: comfortaalight.name
                horizontalAlignment: Text.AlignHCenter

            }
            Image {
                id: windIcon
                asynchronous: true
                Layout.alignment: Qt.AlignCenter
                sourceSize.width : weatherIcon.width
                sourceSize.height : weatherIcon.height
                PropertyAnimation{
                    id : onIndexChangeRotation
                    to : rotationvalue
                    duration : 300
                    property : "rotation"
                    target: windIcon
                }
            }
        }
    }


    ColumnLayout {
        id: errorItem
        visible: false
        spacing: 10
        Layout.alignment: Qt.AlignCenter
        Layout.fillWidth: true
        Layout.fillHeight: true
        Text{
            font.pixelSize: 15
            color:"#ffffff"
            font.family: comfortaalight.name
            id:errorDescription
            Layout.alignment: Qt.AlignCenter
            Layout.margins: 15
            Layout.fillWidth: true
            maximumLineCount:2
            wrapMode:Text.Wrap
        }
        Image{
            id :errorIcon
            asynchronous: true
            Layout.margins: 10
            Layout.alignment: Qt.AlignCenter
            sourceSize.width : 0.5*errorItem.width
            sourceSize.height : errorIcon.width
            fillMode: Image.Stretch
            source: "qrc:/icons/connexion.png"
        }

    }
}

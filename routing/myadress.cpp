#include "myadress.h"

#include <QEventLoop>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <QByteArray>
#include <QEvent>
#include <QDebug>
#include <QObject>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MyAdress::MyAdress(QObject *parent) : QObject(parent)
{

}

QList<double> MyAdress::toCoordinates(QString address){
    address.replace(" ","+");

    qDebug() << address;

    QUrl url("https://nominatim.openstreetmap.org/?format=json&adressdetail=1&q="+address+"&format=json&limit=1");
    QNetworkRequest request(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager();

    //In this part, we create a loop that runs until the QNetworkReply has finished processing.
    QEventLoop loop;
    QObject::connect(manager,
                     SIGNAL(finished(QNetworkReply*)), //finished is a signal from the QNetworkReply Class that is emitted when the reply has finished processing.
                     &loop,
                     SLOT(quit())); //slot from QEventLoop that calls exit()
    QNetworkReply* reply = manager->get(request);
    loop.exec(); //enters the loop and stays in it until loop.exit() is called
    qDebug() << reply;

    QList<double> coord;

    //Put the reply in JSON

    //For Qt -10
    if(reply->error() == QNetworkReply::NoError){

        QString strReply = QString(reply->readAll()); //readAll returns a QByteArray -> we convert it into a String

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonArray jsonArray = jsonResponse.array();
        QJsonValue latitude = jsonArray[0].toObject()["lat"];
        QJsonValue longitude = jsonArray[0].toObject()["lon"];

        coord.append(latitude.toString().toDouble());
        coord.append(longitude.toString().toDouble());
    }

    return coord;
}


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

        coord.append(latitude.toString().toDouble());                       //Attention à la perte de précision
        coord.append(longitude.toString().toDouble());
    }

    return coord;
}

void MyAdress::downloadDataAround(QStringList inputList){
    QDir dir = QDir::currentPath();   //return path in the build folder
    dir.cdUp();                         //project folder
    dir.cd("routing");                  //routing folder
    QString program("python3");
    qDebug() << "List : " << inputList;
    QStringList args = QStringList()<< dir.path()+"/generateTiles.py" << inputList;


    QProcess *p = new QProcess();
    p->setWorkingDirectory(dir.path());
    qDebug() << "Launch script";
    p->startDetached(program, args);
    p->waitForFinished(-1);
    qDebug()<<p->readAll();
    p->close();
}





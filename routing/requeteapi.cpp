#include "requeteapi.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QObject>
#include <QNetworkReply>
#include <QJsonDocument>

RequeteAPI::RequeteAPI()
{

}

QJsonObject RequeteAPI::getAllRoadsAroundThePoint(QString lat, QString lon, QString rad)
{
    //with this url, we get all the roads around a coordinate(latitude,longitude), with a given radius
    QString urlString = "http://overpass-api.de/api/interpreter?data=%3Cosm-script%20output%3D%22json"
            "%22%3E%0A%20%20%3Cquery%20type%3D%22way"
            "%22%3E%0A%20%20%20%20%20%20%3C"
            "around%20lat%3D%22"+lat+
            "%22%20lon%3D%22"+lon+
            "%22%20radius%3D%22"+rad+
            "%22%2F%3E%0A%20%20%20%20%20%20%3Chas-kv%20k%3D%22highway"
            //here we set the roads we want (motorway,trunk,primary,secondary,tertiary,unclassified,residential)
            "%22%20regv%3D%22primary%7Csecondary%7Ctertiary"
            "%22%2F%3E%0A%20%20%3C%2Fquery%3E%0A%20%20%3Cunion%3E%0A%20%20%20%20%3Citem%2F%3E%0A%20%20%20%20%3"
            "Crecurse%20type%3D%22down%22%2F%3E%0A%20%20%3C%2Funion%3E%0A%20%20%3Cprint%2F%3E%0A%3C%2Fosm-script%3E";
    QUrl url(urlString);
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


    //Put the reply in JSON
    QJsonObject jsonObj;
    if(reply->error() == QNetworkReply::NoError)
    {
        QString strReply = QString(reply->readAll());
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        jsonObj = jsonResponse.object();
    }

    //qDebug() << urlString;

    manager->~QNetworkAccessManager();

    return jsonObj;
}


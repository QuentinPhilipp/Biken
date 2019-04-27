#include "weather.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <QByteArray>
#include <QEvent>
#include <QDebug>
#include <QObject>
#include <QEventLoop>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Weather::Weather(){}

Forecast::Forecast(double wDir,
                   double wS,
                   double temp,
                   QString dt,
                   QString wDes,
                   bool active,
                   QString code)
{
    windDirection = wDir;
    windSpeed = wS;
    temperature = temp;
    weatherDescription = wDes;
    this->active = active;
    iconCode = code;
}

void Weather::createForecast(double lat, double lon)
{
    this->lat = lat;
    this->lon = lon;

    QString lats =  QString::number(lat,'f',6),lons =QString::number(lon,'f',6);

    QUrl url("http://api.openweathermap.org/data/2.5/forecast?lat=" + lats + "&lon=" + lons + "&units=metric&APPID=ac69ab213a56edaffaac9baa47770444");
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

    //Put the reply in JSON
    if(reply->error() == QNetworkReply::NoError)
    {
        QString strReply = QString(reply->readAll()); //readAll returns a QByteArray -> we convert it into a String

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();

        int length = jsonObj["list"].toArray().size();
        bool a;
        for (int i=0;i<length;i++) {
            i == 0 ? a = 1 : a = 0;
            forecasts.push_back(Forecast(QJsonValue(jsonObj["list"])[i]["main"]["wind"]["deg"].toDouble(),
                    QJsonValue(jsonObj["list"])[i]["main"]["wind"]["speed"].toDouble(),
                    QJsonValue(jsonObj["list"])[i]["main"]["temp"].toDouble(),
                    QJsonValue(jsonObj["list"])[i]["main"]["dt_txt"].toString(),
                    QJsonValue(jsonObj["list"])[i]["main"]["weather"]["description"].toString(),
                    a,
                    QJsonValue(jsonObj["list"])[i]["main"]["weather"]["icon"].toString()));
        }
    }

}

void Forecast::swapActive()
{
    active ? active = 0 : active = 1;
}

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

#include <QDebug>

Weather::Weather(QObject *parent) : QObject(parent) {}

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
    QStringList str = dt.split(QRegExp("\\s+"));
    qDebug() << dt << "chaine cassee :" << str;
    qDebug() << "Wind : " << windDirection << "   " << windSpeed;
    qDebug() << temperature << "  " << weatherDescription << "with code : " << iconCode;
    qDebug() << "active ? : " << active;
}

void Weather::createForecast(double lat, double lon)
{
    qDebug() << "Starting weather request for coord : " << lat << " , " << lon;
    this->lat = lat;
    this->lon = lon;

    QString lats =  QString::number(lat,'f',7),lons =QString::number(lon,'f',7);

    QUrl url("http://api.openweathermap.org/data/2.5/forecast?lat=" + lats + "&lon=" + lons + "&units=metric&APPID=ac69ab213a56edaffaac9baa47770444");
    QNetworkRequest request(url);

    QNetworkAccessManager *manager2 = new QNetworkAccessManager();

    //In this part, we create a loop that runs until the QNetworkReply has finished processing.
    QEventLoop loop;
    QObject::connect(manager2,
                     SIGNAL(finished(QNetworkReply*)), //finished is a signal from the QNetworkReply Class that is emitted when the reply has finished processing.
                     &loop,
                     SLOT(quit())); //slot from QEventLoop that calls exit()
    QNetworkReply* reply = manager2->get(request);
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
        qDebug() << "length of weather list :" << length;
        for (int i=0;i<length;i++) {
            i == 0 ? a = 1 : a = 0;

            forecasts.push_back(Forecast(QJsonValue(jsonObj["list"])[i]["wind"]["deg"].toDouble(),
                    QJsonValue(jsonObj["list"])[i]["wind"]["speed"].toDouble(),
                    QJsonValue(jsonObj["list"])[i]["main"]["temp"].toDouble(),
                    QJsonValue(jsonObj["list"])[i]["dt_txt"].toString(),
                    QJsonValue(jsonObj["list"])[i]["weather"][0]["description"].toString(),
                    a,
                    QJsonValue(jsonObj["list"])[i]["weather"][0]["icon"].toString()));
            qDebug() << i;
        }
    }
}

void Weather::changeForecast(int id)
{
    for (auto &e : forecasts)
    {
        if (e.getActive())
        {
            e.swapActive();
        }
    }
    forecasts[unsigned(id)].swapActive();
}

int Weather::findActive()
{
    int length = int(forecasts.size());
    for (int i=0;i<length;i++){
        if(forecasts[unsigned(i)].getActive()){return i;}
    }
    return 0;
}

QString Weather::getActiveIcon(){
    int i = findActive();

    if (forecasts.size() == 0){
        qDebug() << "APPEL DU CODE ------------ aucune météo disponible";
        return "qrc:/icons/01d.png";
    }

    QString code = forecasts[unsigned(i)].getIcon();
    qDebug() << "APPEL DU CODE DE L'ICONE   " << code;
    return "qrc:/icons/"+code+".png";

}

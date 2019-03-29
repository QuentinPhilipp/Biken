#include <QApplication>

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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QUrl url("http://api.openweathermap.org/data/2.5/forecast?q=Brest,FR&units=metric&APPID=ac69ab213a56edaffaac9baa47770444");
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
    if(reply->error() == QNetworkReply::NoError)
    {
        QString strReply = QString(reply->readAll()); //readAll returns a QByteArray -> we convert it into a String

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();

        qDebug() << "Ville: " << QJsonValue(jsonObj["city"])["name"].toString();
        int length = jsonObj["list"].toArray().size();
        for (int i=0;i<length;i++) {
            qDebug() << "Date & heure: " << QJsonValue(jsonObj["list"])[i]["dt_txt"].toString();
            qDebug() << "Temperature: " << QJsonValue(jsonObj["list"])[i]["main"]["temp"].toDouble() << "°C\n";
        }
    }

    manager->~QNetworkAccessManager(); 
    return a.exec();
}

/*

Print la meteo pour 5 jours:

Ville:  "Brest"
Date & heure:  "2019-03-29 15:00:00"
Temperature:  14.73 °C

Date & heure:  "2019-03-29 18:00:00"
Temperature:  13.71 °C

Date & heure:  "2019-03-29 21:00:00"
Temperature:  9.36 °C

Date & heure:  "2019-03-30 00:00:00"
Temperature:  7.11 °C

Date & heure:  "2019-03-30 03:00:00"
Temperature:  5.89 °C

Date & heure:  "2019-03-30 06:00:00"
Temperature:  5.42 °C

Date & heure:  "2019-03-30 09:00:00"
Temperature:  12.09 °C

Date & heure:  "2019-03-30 12:00:00"
Temperature:  15.35 °C

Date & heure:  "2019-03-30 15:00:00"
Temperature:  15.31 °C

Date & heure:  "2019-03-30 18:00:00"
Temperature:  12.76 °C

Date & heure:  "2019-03-30 21:00:00"
Temperature:  10.01 °C

Date & heure:  "2019-03-31 00:00:00"
Temperature:  9.06 °C

Date & heure:  "2019-03-31 03:00:00"
Temperature:  9.13 °C

Date & heure:  "2019-03-31 06:00:00"
Temperature:  9.06 °C

Date & heure:  "2019-03-31 09:00:00"
Temperature:  12.2 °C

Date & heure:  "2019-03-31 12:00:00"
Temperature:  14.59 °C

Date & heure:  "2019-03-31 15:00:00"
Temperature:  14.71 °C

Date & heure:  "2019-03-31 18:00:00"
Temperature:  13.15 °C

Date & heure:  "2019-03-31 21:00:00"
Temperature:  10.73 °C

Date & heure:  "2019-04-01 00:00:00"
Temperature:  9.8 °C

Date & heure:  "2019-04-01 03:00:00"
Temperature:  9.32 °C

Date & heure:  "2019-04-01 06:00:00"
Temperature:  8.05 °C

Date & heure:  "2019-04-01 09:00:00"
Temperature:  11.66 °C

Date & heure:  "2019-04-01 12:00:00"
Temperature:  15.21 °C

Date & heure:  "2019-04-01 15:00:00"
Temperature:  15.21 °C

Date & heure:  "2019-04-01 18:00:00"
Temperature:  13.09 °C

Date & heure:  "2019-04-01 21:00:00"
Temperature:  9.09 °C

Date & heure:  "2019-04-02 00:00:00"
Temperature:  8.37 °C

Date & heure:  "2019-04-02 03:00:00"
Temperature:  7.79 °C

Date & heure:  "2019-04-02 06:00:00"
Temperature:  8.43 °C

Date & heure:  "2019-04-02 09:00:00"
Temperature:  9.78 °C

Date & heure:  "2019-04-02 12:00:00"
Temperature:  9.51 °C

Date & heure:  "2019-04-02 15:00:00"
Temperature:  9.83 °C

Date & heure:  "2019-04-02 18:00:00"
Temperature:  8.26 °C

Date & heure:  "2019-04-02 21:00:00"
Temperature:  7.89 °C

Date & heure:  "2019-04-03 00:00:00"
Temperature:  6.82 °C

Date & heure:  "2019-04-03 03:00:00"
Temperature:  7.42 °C

Date & heure:  "2019-04-03 06:00:00"
Temperature:  7.43 °C

Date & heure:  "2019-04-03 09:00:00"
Temperature:  8.07 °C

Date & heure:  "2019-04-03 12:00:00"
Temperature:  8.53 °C

*/

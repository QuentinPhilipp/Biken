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
        for (int i=0;i<jsonObj.length();i++) {
            qDebug() << "Date & heure: " << QJsonValue(jsonObj["list"])[i]["dt_txt"].toString();
            qDebug() << "Temperature: " << QJsonValue(jsonObj["list"])[i]["main"]["temp"].toDouble() << "°C\n";
        }
    }

    manager->~QNetworkAccessManager(); 
    return a.exec();
}

/*

Print in console:

Ville:  "Brest"
Date & heure:  "2019-03-29 00:00:00"
Temperature:  5.94 °C

Date & heure:  "2019-03-29 03:00:00"
Temperature:  4.86 °C

Date & heure:  "2019-03-29 06:00:00"
Temperature:  4.06 °C

Date & heure:  "2019-03-29 09:00:00"
Temperature:  9.54 °C

Date & heure:  "2019-03-29 12:00:00"
Temperature:  13.52 °C

*/
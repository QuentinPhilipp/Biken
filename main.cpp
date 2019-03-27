#include <QApplication>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <QByteArray>
#include <QEvent>
#include <QDebug>
#include <QObject>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QUrl url("http://api.openweathermap.org/data/2.5/forecast?q=Brest,FR&units=metric&APPID=ac69ab213a56edaffaac9baa47770444");
    QNetworkRequest request(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QEventLoop loop;

    QObject::connect(manager,
                     SIGNAL(finished(QNetworkReply*)),
                     &loop,
                     SLOT(quit()));

    QNetworkReply* reply = manager->get(request);
    loop.exec();

    QByteArray response = reply->readAll();

    qDebug() << response;

    manager->~QNetworkAccessManager();

    return a.exec();
}
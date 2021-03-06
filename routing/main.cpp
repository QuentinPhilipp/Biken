#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QTime>
#include <QUrl>
#include <QtWebEngine>
#include <QString>
#include <QApplication>
#include <QLabel>

#include "utils.h"
#include "thread.h"
#include "node.h"
#include "way.h"
#include "myadress.h"
#include "datamanager.h"
#include "card.h"
#include "weather.h"
#include <QSplashScreen>


//QSettings settings("config.ini", QSettings::IniFormat);



int main(int argc, char *argv[])
{
    //for the webengineview
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("QtExamples");
    QApplication app(argc, argv);
//    QGuiApplication app1(argc, argv);

    //creating splash screen
    QPixmap pixmap("../routing/icons/splashScreen.png");
    QSplashScreen splash(pixmap);
    splash.show();
    app.processEvents();


    //create the datamanager class
    QScopedPointer<DataManager> db(new DataManager);

    //Recuperation of the working path

    QDir dir = QDir::currentPath();   //return path in the build folder
    dir.cdUp();                         //project folder
    dir.cd("routing/Data");                  //routing folder
    QString path = dir.path();
    qDebug()<<path;
    
    MyAdress* myAdress = new MyAdress();

    //Création du seveur pour l'échange de données avec la carte géolocalisée
    Thread *thread = new Thread();
    thread->start();


    QStringList departments;
    departments<<"29";                          // add the 29 departement in database if it isn't already in
    db->extendDatabase(departments);
    qDebug()<<"End script database";

    QString defaultAdress = "Loudeac";              //load the database around the adress
    QList<double> defaultCoord = myAdress->toCoordinates(defaultAdress);
    qDebug()<<defaultCoord;
    db->requestRoads(defaultCoord[0],defaultCoord[1],150);   //radius in km    Load the data and convert from database to object

    Weather* weather = new Weather();

    //create the Map class
    Card *carte = new Card(1);
    carte->createGeolocalisedMap();

    //Initialize the HTML code related to the map
    QtWebEngine::initialize();



    //Pour passer du C++ au QML
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("path",path);              //create a variable path and wu use it in our QML
    engine.rootContext()->setContextProperty("weather",weather);        //create a variable weather usable in our QML code
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    engine.rootContext()->setContextProperty("myAdress",myAdress);      //create a variable myAdress usable in our QML code
    engine.rootContext()->setContextProperty("dataManager", db.data()); //create a variable dataManager usable in our QML code
    engine.rootContext()->setContextProperty("maCarte",carte);

    splash.close();
    return app.exec();
}

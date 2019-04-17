#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QTime>

#include "node.h"
#include "way.h"
#include "requeteapi.h"
#include "myadress.h"
#include "datamanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //create the datamanger class
    QScopedPointer<DataManager> db(new DataManager);

    MyAdress* myAdress = new MyAdress();

    //Pour passer du C++ au QML
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;    
    engine.rootContext()->setContextProperty("myAdress",myAdress);
    engine.rootContext()->setContextProperty("dataManager", db.data()); //créer une variable dataManager utilisable dans notre QML

    return app.exec();
}

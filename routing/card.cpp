#include "card.h"
#include "node.h"


//this function can be called in QML
Card::Card(int identifiant)
{
    Card::id=identifiant;
}

//this function can be called in QML
QStringList Card::sendNodes(QVariantList RouteNodes, DataManager *db)       //envoie des coordonnées de chaque Nodes et l'itinéraire [lat,lon]
{
    QStringList nodes;
    int dataLength = RouteNodes.length();
    for(int i=0; i<dataLength ; ++i)
        {
        QVariantList node =db->DataManager::requestLatLonFromNodes(RouteNodes[i]);
        QString lon = node[0].toString();
        QString lat = node[1].toString();
        nodes.append(QStringList()<<"["+lon+","+lat+"]");          //problème : , entre chaque coordonnées
        }
    return nodes;   //this is a list of string wich contains coordinates [lat,lon] --> execution of script python to create a card
}

uint64_t Card::getId() const
{
    return this->id;
}

void Card::createMap(QVariantList RouteNodes, DataManager *db)
{

    QDir dir = QDir::currentPath();   //return path in the build folder
    dir.cdUp();                         //project folder
    dir.cd("routing");                  //routing folder

    QString program("python3");
    QStringList filepath = QStringList()<< dir.path()+"/CardGeneration.py";         //on récupére le path du fichier à éxécuter
    QStringList nodes = QStringList()<<sendNodes(RouteNodes, db);                  //on récupère les nodes a donner en paramètre à notre script de création de carte
    QStringList nodes_command;
    QStringList args = QStringList()<<filepath<<nodes;                             //création de la ligne de commande qui sera envoyée
    qDebug()<<args;
    QProcess p;
    p.setWorkingDirectory(dir.path());
    p.execute(program, args);
}

QString Card::getCurrentPath()
{
    return QDir::currentPath();
}

void Card::createGeolocalisedMap()
{
    QDir dir = QDir::currentPath();   //return path in the build folder
    dir.cdUp();                         //project folder
    dir.cd("routing");
    QString program("python3");
    QStringList args = QStringList()<< dir.path()+"/geolocalisedCardGeneration.py";
    QProcess p;
    p.setWorkingDirectory(dir.path());
    p.execute(program, args);

}




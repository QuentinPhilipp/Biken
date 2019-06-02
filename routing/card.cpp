#include "card.h"
#include "node.h"
#include <QTime>

//this function can be called in QML
Card::Card(int identifiant)
{
    Card::id=identifiant;
}

//this function can be called in QML
int Card::sendNodes(QVariantList RouteNodes, DataManager *db)       //envoie des coordonnées de chaque Nodes et l'itinéraire [lat,lon]
{
    QTime t1;
    t1.start();
    int dataLength = RouteNodes.length();
    //qDebug()<<"reception"<<RouteNodes;
    //création d'un fichier
    QFile file("../routing/Data/coordinates.txt");
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return 1;
    }
    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // Écriture des différentes lignes dans le fichier
    for(int i=0; i<dataLength ; ++i)
    {
        Node * node = db->getNodeFromNodeId(static_cast<unsigned long long>(RouteNodes[i].toDouble()));
        QString lon = QString::number(node->getLongitude());
        QString lat = QString::number(node->getLatitude());
        flux<<lat<<endl<<lon<<endl;
    }
    file.close();
    createMap();
    qDebug() << "Temps pour faire la carte: " << t1.elapsed() << "ms";
    return 0;
}

uint64_t Card::getId() const
{
    return this->id;
}

void Card::createMap()
{

    QDir dir = QDir::currentPath();     //return path in the build folder
    dir.cdUp();                         //project folder
    dir.cd("routing");                  //routing folder

    QString program("python3");
    QStringList filepath = QStringList()<< dir.path()+"/CardGeneration.py";         //on récupére le path du fichier à éxécuter
    QProcess p;
    p.setWorkingDirectory(dir.path());
    //qDebug() << "args : " << args << "\n dir.path : " << dir.path();
    p.execute(program, filepath);
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




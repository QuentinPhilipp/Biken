#include "card.h"
#include "node.h"


//this function can be called in QML
Card::Card(int identifiant)
{
    Card::id=identifiant;
}

//this function can be called in QML
int Card::sendNodes(QVariantList RouteNodes, DataManager *db)       //envoie des coordonnées de chaque Nodes et l'itinéraire [lat,lon]
{
    int dataLength = RouteNodes.length();
    //création d'un fichier
    QFile file("coordinates.txt");
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
        QVariantList node =db->DataManager::requestLatLonFromNodes(RouteNodes[i]);
        QString lon = node[0].toString();
        QString lat = node[1].toString();
        flux<<lon<<endl<<lat<<endl;
    }
    file.close();
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




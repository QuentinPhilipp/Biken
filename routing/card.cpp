#include "card.h"
#include "node.h"


//this function can be called in QML
Card::Card(int identifiant)
{
    Card::id=identifiant;
}

//this function can be called in QML
/*int Card::SendNodes(QVariantList RouteNodes, DataManager db)
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
        QVariantList node =db.DataManager::requestLatLonFromNodes(RouteNodes[i]);
        QString lon = node[0].toString();
        QString lat = node[1].toString();
        flux<<lon<<endl<<lat<<endl;
        }
    file.close();
}*/

uint64_t Card::getId() const
{
    return this->id;
}

void Card::createMap()
{
    QString program("python");
    QStringList args = QStringList()<<QDir::currentPath()+"/CardGeneration.py";
    QProcess p;
    p.setWorkingDirectory(QDir::currentPath());
    p.execute(program, args);
}

QString Card::getCurrentPath()
{
    return QDir::currentPath();
}




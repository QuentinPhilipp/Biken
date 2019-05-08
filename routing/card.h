#ifndef CARD_H
#define CARD_H

#include <QProcess>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QObject>

#include "datamanager.h"

using namespace std;


class Card : public QObject
{
Q_OBJECT
public:
    Card(int identifiant);
    Q_INVOKABLE void createMap();
    uint64_t getId() const;
    //Q_INVOKABLE int SendNodes(QVariantList RouteNodes, DataManager db);  //peut pas passer db en param car c'est UNIQUEMENT un objet QML
private:
    int id;
};

#endif // CARD_H

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
    Q_INVOKABLE QString getCurrentPath();
    Q_INVOKABLE int sendNodes(QVariantList RouteNodes, DataManager *db);
private:
    int id;
};

#endif // CARD_H

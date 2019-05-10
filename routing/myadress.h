#ifndef MYADRESS_H
#define MYADRESS_H

#include <QObject>
#include <QProcess>
#include <QDir>
#include "datamanager.h"

class MyAdress : public QObject
{
    Q_OBJECT
    QList<QString> downloadedRegion;    //List of string with the id of department downloaded    ex : ["29","56","57"...]

public:
    explicit MyAdress(QObject *parent = nullptr);
    void downloadDataAround(QStringList list);


signals:

public slots:
    QList<double> toCoordinates(QString address);

};

#endif // MYADRESS_H

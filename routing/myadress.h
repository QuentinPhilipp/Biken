#ifndef MYADRESS_H
#define MYADRESS_H

#include <QObject>

//This object is empty, it allows the QML module to call the fucntion through an object.
//The function use Numeratim API to check for matching coordinates for any adress given.

class MyAdress : public QObject
{
    Q_OBJECT
public:
    explicit MyAdress(QObject *parent = nullptr);

signals:

public slots:
    QList<double> toCoordinates(QString address);
};

#endif // MYADRESS_H

#ifndef MYADRESS_H
#define MYADRESS_H

#include <QObject>

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

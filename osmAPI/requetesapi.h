#ifndef REQUETESAPI_H
#define REQUETESAPI_H

#include <QString>
#include <QJsonObject>

class RequetesAPI
{
public:
    RequetesAPI();
    QJsonObject getAllRoadsAroundThePoint(QString lat,QString lon,QString rad);
private:
    QString latitude;
    QString longitude;
    QString radius;
};

#endif // REQUETESAPI_H
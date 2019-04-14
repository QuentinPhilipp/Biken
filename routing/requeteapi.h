#ifndef REQUETEAPI_H
#define REQUETEAPI_H

#include <QString>
#include <QJsonObject>

class RequeteAPI
{
public:
    RequeteAPI();
    QJsonObject getAllRoadsAroundThePoint(QString lat,QString lon,QString rad);
};

#endif // REQUETEAPI_H

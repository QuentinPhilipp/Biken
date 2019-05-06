#ifndef REQUETEAPI_H
#define REQUETEAPI_H

#include <QString>
#include <QJsonObject>
#include <QList>
#include "node.h"
#include "way.h"
#include <tuple>

class RequeteAPI
{
public:
    RequeteAPI();
    std::tuple<std::vector<Way>, std::vector<Node>> requestToDatabase(QString lat,QString lon,QString rad);
};

#endif // REQUETEAPI_H

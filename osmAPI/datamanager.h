#ifndef DATAMANAGER_H
#define DATAMANAGER_H


#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QObject>


class dataManager
{
public:
    dataManager();
    void addValuesNodes(uint64_t id, double latitude, double longitude);
    void addValuesWays(uint64_t id, uint64_t node);
    std::vector<QVariant> requestNodesFromRoad(uint64_t idRoad);
    std::tuple<QVariant,QVariant> requestLatLonFromNodes(uint64_t idNode);
private:
    void addTables();
};

#endif // DATAMANAGER_H

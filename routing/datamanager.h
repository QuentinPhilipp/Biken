#ifndef DATAMANAGER_H
#define DATAMANAGER_H


#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QObject>


class DataManager
{
public:
    DataManager();
    void addValuesNodes(uint64_t id, double latitude, double longitude);
    void addValuesWays(uint64_t id, uint64_t node);

    std::vector<QVariant> requestNodesFromRoad(uint64_t idRoad);
    std::vector<QVariant> requestNodesFromRoad(QVariant idRoad);

    std::vector<QVariant> requestRoadsFromNode(uint64_t idNode);
    std::vector<QVariant> requestRoadsFromNode(QVariant idNode);

    std::tuple<QVariant,QVariant> requestLatLonFromNodes(uint64_t idNode);
    QVariantList requestLatLonFromNodes(QVariant idNode);

    std::vector<QVariant> requestNodeFromLatLon(double lat, double lon);

    QVariantList findRouteFrom(double lat, double lon);
private:
    void addTables();
};

#endif // DATAMANAGER_H

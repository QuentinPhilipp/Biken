#include "datamanager.h"
#include <string>
#include <QDebug>
#include <QObject>
#include <QJsonObject>
#include <vector>
#include <algorithm>
#include <QJsonArray>
#include <tuple>
#include <QTime>
#include <QtMath>


using namespace std;

DataManager::DataManager(QObject *parent) : QObject(parent)
{
    // create the dataBase
    const QString DRIVER("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(DRIVER))                                    //checking the availability of the driver
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);                       //Adding the driver
        db.setDatabaseName("../Database.db");                                  //path for the database    |    do not create a WaysAndNodes.db, it's done automatically

        //open the database
        if(!db.open())
        {qDebug() << "ERROR opening the database ";}
        else
        {qDebug() << "DataBase opened properly";}                                                            //create tables
    }
    else {
        qDebug() << "ERROR Driver not Available";
    }
}


Node DataManager::getNodeFromNodeId(unsigned long long nodeId, vector<Node> &nodeObjectVector)
{
    /*
     * Ici, pour parcourir tous les objects node (sachant qu'il y en a énormément), j'utilise la méthode du juste prix:
     * Cela permet par exemple de retrouver un élément dans une liste de 1 000 000 d'éléments en seulement une vingtaine d'opérations.
     */
    unsigned long long i = nodeObjectVector.size()-1;
    Node node = nodeObjectVector[i];
    unsigned long long id;
    unsigned long long prev_i=0;
    unsigned long long temporaryValue=0;
    unsigned long long valueToSubstract;
    while(true){
        node = nodeObjectVector[i];
        id =node.getId();
        if(id==nodeId){
            return node;
        }
        else {
            temporaryValue=i;
            if(i>prev_i){
                valueToSubstract=(i-prev_i)/2;
            }
            else {
                valueToSubstract=(prev_i-i)/2;
            }

            if(valueToSubstract==0){ //I had to add this because in the last operation we can have: (prev_i-i=1), so valueToSubstract would be 1/2=0
                valueToSubstract=1;
            }

            if(id>nodeId){
                i-=valueToSubstract;
            }
            else{
                i+=valueToSubstract;
            }
            prev_i=temporaryValue;
        }
    }
}

vector<Node>
DataManager::requestNodesFromRoad(unsigned long long idRoad)
{
    //converting
    QVariant idRoadVar;
    idRoadVar.setValue(idRoad);
    QSqlQuery query;

    //preparing query
    query.prepare("SELECT id_node,latitude,longitude FROM nodes, ways WHERE (id_node=node) and (id_way = ? )");
    query.addBindValue(idRoadVar);


    //execute
    if(!query.exec())
        qWarning() << "ERROR Finding nodes: " << query.lastError().text();

    //add all the nodes of the result in a vector
    vector<Node> nodes;
    while (query.next()) {
        unsigned long long id = static_cast<unsigned long long>(query.value(0).toDouble());
        double lat = query.value(1).toDouble();
        double lon = query.value(2).toDouble();
        Node n = Node(id,lat,lon);
        nodes.emplace_back(n);
    }
    return nodes;
}

vector<Node>    //overload
DataManager::requestNodesFromRoad(QVariant idRoad)
{
    QSqlQuery query;

    //preparing query
    query.prepare("SELECT id_node,latitude,longitude FROM nodes, ways WHERE (id_node=node) and (id_way = ? )");
    query.addBindValue(idRoad);


    //execute
    if(!query.exec())
        qWarning() << "ERROR Finding nodes: " << query.lastError().text();

    //add all the nodes of the result in a vector
    vector<Node> nodes;
    while (query.next()) {
        unsigned long long id = static_cast<unsigned long long>(query.value(0).toDouble());
        double lat = query.value(1).toDouble();
        double lon = query.value(2).toDouble();
        Node n = Node(id,lat,lon);
        nodes.emplace_back(n);
    }
    return nodes;
}

vector<Way>
DataManager::requestRoadsFromNode(Node node)
{
    //add all the nodes of the result in a vector
    vector<Way> roadsInLat;

    //In this part (until the third while loop) we want to get all the roads that are between two latitudes (wantedLat-0.02 and wantedLat+0.02)
    //Basically, those 2 latitudes can be represented on a map by two horizontal parallels (one 2km above wantedLat and one 2km below)
    unsigned long long i = allWays.size()-1;
    Way way = allWays[i]; //allWays is the vector containing every single road that was in the database
    double lat;
    double wantedLat=node.getLatitude();
    unsigned long long prev_i=0;
    unsigned long long temporaryValue=0;
    unsigned long long valueToSubstract;
    bool b = false;
    while(true){
        //In this loop, we go through allWays to find one Way that is less than 2km from the wanted latitude.
        //As soon as one is found, exit the while loop
        way = allWays[i];
        lat =way.getCenterNode().getLatitude();
        if(lat>=wantedLat-0.02 && lat<=wantedLat+0.02){ //0.02 in lat is ~2km
            break;
        }
        else {
            temporaryValue=i;
            if(i>prev_i){
                valueToSubstract=(i-prev_i)/2;
            }
            else {
                valueToSubstract=(prev_i-i)/2;
            }

            if(valueToSubstract==0){
                valueToSubstract=1;
                if(b==true){
                    break;
                }
                b=true;
            }

            if(lat>wantedLat){
                i-=valueToSubstract;
            }
            else{
                i+=valueToSubstract;
            }
            prev_i=temporaryValue;
        }
    }
    while(true){
        //In this loop, we start from the way found in the previous loop and we go down the list "allWays" to find the Way with
        //the lowest latitude (the ways in allWays are ordered from the lowest latitude to the highest)
        //Once it has been found, exit the loop
        if(i<=0){
            break;
        }
        way = allWays[i];
        lat =way.getCenterNode().getLatitude();
        if(!(lat>=wantedLat-0.02 && lat<=wantedLat+0.02)){
            break;
        }
        if(i<=0){
            break;
        }
        i--;
    }
    i=i<allWays.size()?i+1:allWays.size();//security
    while(true){
        //In this loop, we start from the Way with the lowest latitude (found in the loop before) and we go up in the list "allWays"
        //one way at a time (adding it in a list "roadsInLat" every time), until a Way is more than 2km from the wanted latitude (->exit the loop)
        way = allWays[i];
        lat =way.getCenterNode().getLatitude();
        if(lat>=wantedLat-0.02 && lat<=wantedLat+0.02){
            roadsInLat.emplace_back(way);
        }
        else{
            break;
        }
        if(i==allWays.size()-1){
            break;
        }
        i++;
    }

    //Once we have all the roads between the 2 latitudes (which drastically reduce the amount of roads to deal with), we go through the
    //list "roadsInLat". For each Way in this list: if its centerNode is less than 2km from the wanted longitude, we look if this Way
    //contains the wanted Node. If so, we add this way in the list "roadsAtThatNode".
    double lon;
    double wantedLon=node.getLongitude();
    unsigned long long wantedId = node.getId();
    vector<Way> roadsAtThatNode;
    for(auto &road:roadsInLat){
        lon =road.getCenterNode().getLongitude();
        if(lon>=wantedLon-0.03 && lon<=wantedLon+0.03){ //0.03 in longitude is ~2km in France
            for(auto &n:road.getNodes()){
                if(n.getId()==wantedId){
                    roadsAtThatNode.emplace_back(road);
                    break;
                }
            }
        }
    }
    return roadsAtThatNode;
}

//This function stores every roads from the database in a vector of Way
void DataManager::requestRoads(double lat,double lon,double rad)
{
    QSqlQuery query;

    double radNode = rad +15.0;               //increasing radius to be sure to have all point from big roads

    //converting
    double minLatNode = lat - radNode/111.11;
    double maxLatNode = lat + radNode/111.11;
    double minLat = lat - rad/111.11;
    double maxLat = lat + rad/111.11;
    double minLonNode,maxLonNode,minLon,maxLon;
    if (lon >= 0)
    {
        minLonNode = lon - radNode/(111.11*cos(lat));           //Pour la longitude il faut faire * cos(latitude) car 1° =111.11 a l'equateur mais pas partout
        maxLonNode = lon + radNode/(111.11*cos(lat));
        minLon = lon - rad/(111.11*cos(lat));           //Pour la longitude il faut faire * cos(latitude) car 1° =111.11 a l'equateur mais pas partout
        maxLon = lon + rad/(111.11*cos(lat));
    }
    else {
        minLonNode = lon + radNode/(111.11*cos(lat));
        maxLonNode = lon - radNode/(111.11*cos(lat));
        minLon = lon + rad/(111.11*cos(lat));
        maxLon = lon - rad/(111.11*cos(lat));
    }

    allNodes= createNodeObject(query,minLatNode,maxLatNode,minLonNode,maxLonNode);
    allWays= createWayObject(query,minLat,maxLat,minLon,maxLon,getAllNodes());
    qDebug() << "Allways size : "<<allWays.size();
    qDebug() << "AllNodes size : "<<allNodes.size();

}

vector<Node> DataManager::createNodeObject(QSqlQuery query,double minLat,double maxLat,double minLon,double maxLon){
    query.prepare("SELECT DISTINCT id_node,latitude,longitude FROM roads WHERE ((:minLat<=centerLat) and (centerLat<=:maxLat) and (:minLon<=centerLon) and (centerLon<=:maxLon)) ORDER BY id_node");
    query.bindValue(":minLat",minLat);
    query.bindValue(":maxLat",maxLat);
    query.bindValue(":minLon",minLon);
    query.bindValue(":maxLon",maxLon);

    if(!query.exec()){
        qWarning() << "ERROR Finding roads in RequestRoad: " << query.lastError().text();
    }

    qDebug() << "Query Node finish";
    query.first();
    vector<Node> nodeVect;
    while (query.next()) {
        unsigned long long idNode = static_cast<unsigned long long>(query.value(0).toDouble());
        double lat = query.value(1).toDouble();
        double lon = query.value(2).toDouble();
        Node n = Node(idNode,lat,lon);
        nodeVect.emplace_back(n);
    }
    qDebug() << "Node created : "<< nodeVect.size();
    return nodeVect;
}

vector<Way> DataManager::createWayObject(QSqlQuery query,double minLat,double maxLat,double minLon,double maxLon,std::vector<Node> nodeVect){
    //preparing query
    query.prepare("SELECT DISTINCT id_way,centerLat,centerLon,id_node,oneway,roundabout,maxspeed,type,latitude,longitude FROM roads WHERE ((:minLat<=centerLat) and (centerLat<=:maxLat) and (:minLon<=centerLon) and (centerLon<=:maxLon)) ORDER BY centerLat,id_way");
    query.bindValue(":minLat",minLat);
    query.bindValue(":maxLat",maxLat);
    query.bindValue(":minLon",minLon);
    query.bindValue(":maxLon",maxLon); // JOIN nodes ON ways.node = nodes.id_node

    //execute
    if(!query.exec()){
        qWarning() << "ERROR Finding roads in RequestRoad: " << query.lastError().text();
    }

    qDebug() << "Query Ways finish";


    query.first();
    //add all the nodes of the result in a vector
    vector<Node> wayNodes;
    vector<Way> wayVector;
    unsigned long long lastId = static_cast<unsigned long long>(query.value(0).toDouble());
    Node centerNode;
    bool oneway = false;
    bool roundabout = false;
    int maxspeed = 0;
    QString type;
    unsigned long long idNode = static_cast<unsigned long long>(query.value(3).toDouble());

    if ((query.value(8).toDouble()-0.00001<query.value(1).toDouble() && query.value(1).toDouble()<query.value(8).toDouble()+0.00001) && (query.value(9).toDouble()-0.00001<query.value(2).toDouble() && query.value(2).toDouble()<query.value(9).toDouble()+0.00001)) //comparaison == impossible with double     //current Node is the CenterNode
    {
        centerNode = getNodeFromNodeId(idNode,nodeVect);
    }

    Node n = getNodeFromNodeId(idNode,nodeVect);                        // add the first Node
    wayNodes.emplace_back(n);

    while (query.next()) {
        unsigned long long idWay = static_cast<unsigned long long>(query.value(0).toDouble());
        if (idWay != lastId)                                                                                    // can't go there without a full circle in the while() bc way are at least 2 node long
        {
            Way w = Way(lastId,wayNodes,centerNode,oneway,roundabout,maxspeed,type);
            wayVector.emplace_back(w);
            lastId = static_cast<unsigned long long>(query.value(0).toDouble());
            wayNodes={};
        }
        unsigned long long idNode = static_cast<unsigned long long>(query.value(3).toDouble());
        oneway = query.value(4).toBool();
        roundabout = query.value(5).toBool();
        maxspeed = query.value(6).toInt();
        QString type = query.value(7).toString();

        if ((query.value(8).toDouble()-0.00001<query.value(1).toDouble() && query.value(1).toDouble()<query.value(8).toDouble()+0.00001) && (query.value(9).toDouble()-0.00001<query.value(2).toDouble() && query.value(2).toDouble()<query.value(9).toDouble()+0.00001)) //comparaison == impossible with double     //current Node is the CenterNode
        {
            centerNode = getNodeFromNodeId(idNode,nodeVect);
        }
        Node n = getNodeFromNodeId(idNode,nodeVect);
        wayNodes.emplace_back(n);
    }
    Way w = Way(lastId,wayNodes,centerNode,oneway,roundabout,maxspeed,type);            // add last way
    wayVector.emplace_back(w);
    qDebug() << "Way created : " << wayVector.size();
    return wayVector;
}

QVariantList DataManager::requestLatLonFromNodes(QVariant idNode)
{
    QSqlQuery query;
    //preparing query
    query.prepare("SELECT latitude,longitude FROM nodes WHERE id_node = ?");
    query.addBindValue(idNode);

    //execute
    if(!query.exec())
        qWarning() << "ERROR Finding nodes: " << query.lastError().text();

    //returning a tuple with latitude and longitude. If it doesn't work, you don't have c++17 so look to the tie() function to get the data fro this function
    QVariantList nodes;
    if (query.first()) {
        QVariant lat = query.value(0);
        QVariant lon = query.value(1);
        nodes.append(lat);
        nodes.append(lon);
    }
    //qDebug() << nodes;
    return nodes;
}

//not working yet
//vector<QVariant> DataManager::requestNodeFromLatLon(double lat, double lon)
//{
//    /*
//     *TO DO:
//     * - try to find a node with the exact same latitude and longitude as the coordinate(lat,lon) --- ex:(48.483652,-4.235684)
//     * - if it doesn't exist : remove one (or more) decimal from lat and lon and try to           --- ex: between(48.483,-4.235)
//     *   find a node in this range                                                                ---     and    (48.484,-4.236)
//     * to do that, use this method: lat=floor(lat*10000)/10000 (adjusting "10000" depending on how
//     * many decimal you want to remove). You have to include <math.h>
//     *
//     */

//    //converting
//    QVariant latitude, longitude;
//    latitude.setValue(lat);
//    longitude.setValue(lon);
//    QSqlQuery query;

//    //preparing query
//    query.prepare("SELECT id_node FROM nodes WHERE latitude = ? AND longitude = ?");
//    query.addBindValue(latitude);
//    query.addBindValue(longitude);

//    //execute
//    if(!query.exec())
//      qWarning() << "ERROR Finding nodes: " << query.lastError().text();
//}

QVariantList DataManager::findRouteFrom(double lat, double lon)
{
    /*
     * TO DO (propositions):
     *
     * 1)
     * - appeler la fonction requestNodeFromLatLon(lat,lon) qui retourne le node le plus proche des coordonnées (lat,lon)
     * - trouver un way qui contient ce node
     * - partir de ce node et passer au node suivant (dans le même Way) jusqu'à ce qu'on croise un autre Way (=jusqu'à ce qu'un node soit
     *   contenu dans plus de 1 Way)
     * - à partir de ce node "de croisement", rester dans le même way ou changer de way (en fonction des possibilités)
     * - continuer en allant de way en way jusqu'à ce qu'on ait atteint x km
     * - revenir au point de départ de la même manière, par une autre route
     *
     * - attention aux oneway roads et aux roundabout ...
     */
    QVariantList routeNodes; //what will be returned to QML
    unsigned long long roadId = 136110431;
    vector<Node> nodes = requestNodesFromRoad(roadId);
    Node node;
    Node previous_node = nodes[0];
    qDebug() << "findRouteFrom(): example of QVariant node: " << previous_node.getId();
    routeNodes.append(QVariant(previous_node.getId()));
    int i=0;
    while(i<100){
        bool b=0; //used later, to avoid to stay on the same node
        unsigned long long l = 0;
        unsigned long long nextNode;
        //si le premier noeud du chemin contient plusieurs chemins, et que ce n'est pas le noeud depuis lequel on est entré sur ce chemin:
        if(requestRoadsFromNode(nodes[0]).size()>1 && nodes[0].getId()!=previous_node.getId()){
            node=nodes[0];
            vector<Way> roads = requestRoadsFromNode(node);
            routeNodes.append(QVariant(node.getId())); //if we change of road, append the node in common of the previous and the new road
            previous_node=node;
            unsigned long long newRoadId = roads[0].getId();
            if(newRoadId!=roadId){
                nodes = requestNodesFromRoad(newRoadId);
                roadId=newRoadId;
            }
            else{
                newRoadId = roads[1].getId();
                nodes = requestNodesFromRoad(newRoadId);
                roadId=newRoadId;
            }
        }
        //si le dernier noeud du chemin contient plusieurs chemisn, et que ce n'est pas le noeud depuis lequel on est entré sur ce chemin:
        else if(requestRoadsFromNode(nodes[nodes.size()-1]).size()>1 && nodes[nodes.size()-1].getId()!=previous_node.getId()){
            node=nodes[nodes.size()-1];
            vector<Way> roads = requestRoadsFromNode(node);
            routeNodes.append(QVariant(node.getId())); //if we change of road, append the node in common of the previous and the new road
            previous_node=node;
            unsigned long long newRoadId = roads[0].getId();
            if(newRoadId!=roadId){
                nodes = requestNodesFromRoad(newRoadId);
                roadId=newRoadId;
            }
            else{
                newRoadId = roads[1].getId();
                nodes = requestNodesFromRoad(newRoadId);
                roadId=newRoadId;
            }
        }
        else{
            for(unsigned long long j=0; j<nodes.size(); j++){
                //Those conditions are to see where the node, in common with the previous road, is in the current road.
                //Then it goes through the node list one by one
                if(nodes[0].getId()==previous_node.getId()){
                    nextNode=j;
                }
                else if (nodes[nodes.size()-1].getId()==previous_node.getId()){
                    nextNode=nodes.size()-1-j;
                }
                else{
                    if(!l){
                        for(unsigned long long k=0; k<nodes.size(); k++){
                            if(nodes[k].getId()==previous_node.getId()){
                                l=k;
                                break;
                            }
                        }
                    }
                    if(l+j>=nodes.size()){
                        break;
                    }
                    nextNode=l+j;
                }
                node=nodes[nextNode];
                vector<Way> roads = requestRoadsFromNode(node); //get all the roads that contain the current node
                //At every node, check if there are any road that contains the current node (exept the one road we are currently on)
                if(roads.size()>1 && b>=1){ //b is used to wait one node after you've changed from one road to another. Otherwise it would stay undefinitely on the same node.
                    //if we change of road, append the node in common between the previous and the new road
                    routeNodes.append(QVariant(node.getId()));
                    previous_node=node;
                    unsigned long long newRoadId = roads[0].getId();
                    if(newRoadId!=roadId){
                        nodes = requestNodesFromRoad(newRoadId);
                        roadId=newRoadId;
                    }
                    else{
                        newRoadId = roads[1].getId();
                        nodes = requestNodesFromRoad(newRoadId);
                        roadId=newRoadId;
                    }
                    break;
                }
                b=1;
            }
        }
        i++;
    }
    return routeNodes;
}



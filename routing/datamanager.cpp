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


using namespace std;

DataManager::DataManager(QObject *parent) : QObject(parent)
{
    // create the dataBase
    const QString DRIVER("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(DRIVER))                                    //checking the availability of the driver
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);                       //Adding the driver
        db.setDatabaseName("../WaysAndNodes.db");                                  //path for the database    |    do not create a WaysAndNodes.db, it's done automatically

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

//This function is called from QML
void DataManager::generateWaysAndNodes(QVariant radius)
{
    //Make an API request to get all the roads around a point & calculate the time it takes to receive it.
    RequeteAPI *requeteRoads = new RequeteAPI();
    qDebug() << "\n\n TEST CHRONO rayon = " << radius.toString().toDouble() << "metres.\n";
    QDateTime beforeRequestTime = QDateTime::currentDateTime();
    QJsonObject allRoads = requeteRoads->getAllRoadsAroundThePoint("48.434420","-4.640103",radius.toString());
    QDateTime afterRequestTime = QDateTime::currentDateTime();
    qDebug() << "\nTemps écoulé pendant la requête : "<<beforeRequestTime.secsTo(afterRequestTime)<<"secondes.";

    //Then store everything in objects
    vector<Way> wayObjectVector;                                               //A vector that contains every Way objects
    vector<Node> nodeObjectVector;                                             //A vector that contains every Node objects
    int length = allRoads["elements"].toArray().size();                        //allRoads["elements"] contains all the ways and nodes (in JSON)
    for (int i=0;i<length;i++) {
        QJsonObject element = allRoads["elements"].toArray()[i].toObject();    //element contains one way OR one node (with everything that's inside it), (in JSON)
        if(element["type"]=="node"){
            unsigned long long nodeId = static_cast<unsigned long long>(element["id"].toDouble()); //it has to be unsigned long long because the Id can be more than 2^32 (so uint_32_t and below won't work)
            double latitude = element["lat"].toDouble();
            double longitude = element["lon"].toDouble();
            Node node = Node(nodeId,latitude,longitude);                       //create an object Node with the 3 parameters from above
            nodeObjectVector.emplace_back(node);
        }
        else if(element["type"]=="way"){
            vector<unsigned long long> nodeIdVector;                                     //A vector that contains all the Node objects' Id of one object Way                                      //A vector that contains all the Node objects of one object Way
            unsigned long long id = static_cast<unsigned long long>(element["id"].toDouble());     //get the id in unsigned long long (same reason as above)
            unsigned long long centerNodeId;
            QJsonArray nodeArray = element["nodes"].toArray();                 //nodsArray contains all the node from one way (in JSON)
            int i=0;
            for(auto node : nodeArray)
            {
                unsigned long long nodeId = static_cast<unsigned long long>(node.toDouble());
                nodeIdVector.emplace_back(nodeId);
                if(i==nodeArray.size()/2){
                    centerNodeId = nodeId;
                }
                i++;
            }
            if (nodeIdVector.size()!=0) //security
            {
                Node centerNode = getNodeFromNodeId(centerNodeId, nodeObjectVector);
                Way w = Way(id,nodeIdVector,centerNode);                                  //creating the way with the parameters from above
                wayObjectVector.emplace_back(w);
            }
        }
    }
    allNodes=nodeObjectVector;
    //Finally, store it in the database
    addTables();
    addValuesWays(wayObjectVector);
    QDateTime deux = QDateTime::currentDateTime();
    qDebug() << "\nTemps écoulé pendant la création de ways : "<<afterRequestTime.secsTo(deux)<<"secondes\n";
    addValuesNodes(nodeObjectVector);
    QDateTime afterDatabaseTime = QDateTime::currentDateTime();
    qDebug() << "\nTemps écoulé pendant la création de nodes : "<<afterRequestTime.secsTo(afterDatabaseTime)<<"secondes\n";
}

Node DataManager::getNodeFromNodeId(unsigned long long nodeId, vector<Node> &nodeObjectVector)
{
    /*
     * Ici, pour parcourir tous les objects node (sachant qu'il y en a énormément), j'utilise la méthode du juste prix:
     * Cela permet par exemple de retrouver un élément dans une liste de 1 000 000 d'éléments en seulement une vingtaine d'opérations.
     */
    uint i = nodeObjectVector.size()-1;
    Node node = nodeObjectVector[i];
    unsigned long long id;
    uint prev_i=0;
    uint temporaryValue=0;
    uint valueToSubstract;
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

void DataManager::addTables()
{   /* This functions create the tables
      Tables are only created the first time. If the
      database already exist, tables will not be created*/

    //Adding the ways table
    QSqlQuery clearWays("DELETE FROM ways");                                             //clear the table first
    QSqlQuery queryways("CREATE TABLE IF NOT EXISTS ways (id_way BIGINT, centerLat DOUBLE, centerLon DOUBLE, node BIGINT)"); //using BIGINT to fit with unsigned long long
    if(!queryways.exec())
    {qDebug()<<"Error creating ways table"<<queryways.lastError();}


    //Adding the node table
    QSqlQuery clearNodes("DELETE FROM nodes");                                           //clear the table first
    QSqlQuery querynodes("CREATE TABLE IF NOT EXISTS nodes (id_node BIGINT, latitude DOUBLE, longitude DOUBLE)");
    if(!querynodes.exec())
    {qDebug()<<"Error creating node table"<<querynodes.lastError();}
}

void DataManager::addValuesNodes(vector<Node> nodesVector)
{
    qDebug() << "\n~~ Adding nodes ~~";
    qDebug() << "In progress...";

    int cutValue = 15000;                                                                   //we split the queryString if there is more than n values to append
    int i = 0;                                                                              //this help the programm to run faster
    while (!nodesVector.empty())
    {
        i = 0;                                                                              //reset the counter
        QSqlQuery query;
        QString queryString = "INSERT INTO nodes(id_node,latitude,longitude) VALUES ";           //preparing the beginning of each query
        while (i<cutValue)
        {
            unsigned long long id = nodesVector[0].getId();
            double valueAsDouble = 1.2;
            QString valueAsString = QString::number(valueAsDouble);
            QString add = "("+QString::fromStdString(std::to_string(id))+","+QString::number(nodesVector[0].getLatitude(),'f',8)+","+QString::number(nodesVector[0].getLongitude(),'f',8)+"),";
            /*the string looks like : "(1215779765,48.4368521,-4.6501655"
              QString::number(aDoubleValue,'f',8) is used to cast double
            to QString with 8 numbers precision, so we don't lose data*/
            queryString = queryString + add;                                                //adding the string to the query
            nodesVector.erase(nodesVector.begin());                                         //pop the first element of the vector

            if(nodesVector.empty()){
                break;
            }
            i++;                                                                            //increment counter to detect when we have to split the querry

        }
        int pos = queryString.lastIndexOf(QChar(','));                                      //this 2 lines help to remove the last "," in the end of the query
        queryString = queryString.left(pos);

        query.prepare(queryString);                                                         //preparing query

        if(!query.exec())                                                                   //Execute
          qWarning() << "ERROR Adding nodes: " << query.lastError().text();
    }
    qDebug() << "~~ All nodes added ~~";
}

void DataManager::addValuesWays(vector<Way> wayVector)
{
    qDebug() << "\n~~ Adding ways ~~";
    qDebug() << "In progress ...";

    int cutValue = 15000;                                                                   //we split the queryString if there is more than n values to append
    int i = 0;                                                                              //this help the programm to run faster
    while (!wayVector.empty())
    {
        i = 0;                                                                              //reset the counter
        QSqlQuery query;
        QString queryString = "INSERT INTO ways(id_way,centerLat,centerLon,node) VALUES ";                          //preparing the beginning of each query
        while (i<cutValue)
        {
            unsigned long long id = wayVector[0].getId();
            Node centerNode = wayVector[0].getCenterNode();
            int counter = 0;                                                                //to be sure to add all the node of a way, we don't split querry in a way. We wait the end
                                                                                            //of this way. So we add a counter to add in "i" the good number
            for (auto &node : wayVector[0].getNodesId()){
                counter +=1;
                QString add = "("+QString::fromStdString(std::to_string(id))+","+QString::fromStdString(std::to_string(centerNode.getLatitude()))+","
                        +QString::fromStdString(std::to_string(centerNode.getLongitude()))+","+QString::fromStdString(std::to_string(node))+"),";
                queryString = queryString + add;
            }
            wayVector.erase(wayVector.begin());                                             //pop the first element of the vector
            if(wayVector.empty()){
                break;
            }
            i+=counter;                                                                     //increment counter to detect when we have to split the querry
        }
        int pos = queryString.lastIndexOf(QChar(','));                                      //this 2 lines help to remove the last "," in the end of the query
        queryString = queryString.left(pos);

        query.prepare(queryString);                                                         //preparing query

        if(!query.exec())                                                                   //Execute
          qWarning() << "ERROR Adding ways: " << query.lastError().text();
    }
    qDebug() << "~~ Ways added ~~";


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
DataManager::requestRoadsFromNode(unsigned long long idNode)
{
     //converting
     QVariant idNodeVar;
     idNodeVar.setValue(idNode);
     QSqlQuery query;

     //preparing query
     query.prepare("SELECT id_way, id_node,latitude,longitude FROM nodes,ways WHERE id_way IN (SELECT id_way FROM nodes, ways WHERE (id_node = node) and (id_node=?)) and (id_node=node) ORDER BY id_way");
     query.addBindValue(idNodeVar);

     //execute
     if(!query.exec())
       qWarning() << "ERROR Finding roads: " << query.lastError().text();

     query.first();
     //add all the nodes of the result in a vector
     vector<Way> roads;
     unsigned long long lastId = static_cast<unsigned long long>(query.value(0).toDouble());
     vector<Node> nodeVect;
     vector<unsigned long long> nodeIdVect;

     while (query.next()) {
         unsigned long long idWay = static_cast<unsigned long long>(query.value(0).toDouble());
         if (idWay != lastId)
         {
             Way w = Way(lastId,nodeIdVect,nodeVect);
             roads.emplace_back(w);
             lastId = static_cast<unsigned long long>(query.value(0).toDouble());
             nodeIdVect={};
             nodeVect={};
         }
         unsigned long long idNode = static_cast<unsigned long long>(query.value(1).toDouble());
         double lat = query.value(2).toDouble();
         double lon = query.value(3).toDouble();
         Node n = Node(idNode,lat,lon);
         nodeVect.emplace_back(n);
         nodeIdVect.emplace_back(idNode);
     }
     Way w = Way(lastId,nodeIdVect,nodeVect);
     roads.emplace_back(w);
     return roads;
}

vector<Way>
DataManager::requestRoadsFromNode(QVariant idNode)
{
    QSqlQuery query;

    //preparing query
    query.prepare("SELECT id_way, id_node,latitude,longitude FROM nodes,ways WHERE id_way IN (SELECT id_way FROM nodes, ways WHERE (id_node = node) and (id_node=?)) and (id_node=node) ORDER BY id_way");
    query.addBindValue(idNode);

    //execute
    if(!query.exec())
      qWarning() << "ERROR Finding roads: " << query.lastError().text();

    query.first();
    //add all the nodes of the result in a vector
    vector<Way> roads;
    unsigned long long lastId = static_cast<unsigned long long>(query.value(0).toDouble());
    vector<Node> nodeVect;
    vector<unsigned long long> nodeIdVect;

    while (query.next()) {
        unsigned long long idWay = static_cast<unsigned long long>(query.value(0).toDouble());
        if (idWay != lastId)
        {
            Way w = Way(lastId,nodeIdVect,nodeVect);
            roads.emplace_back(w);
            lastId = static_cast<unsigned long long>(query.value(0).toDouble());
            nodeIdVect={};
            nodeVect={};
        }
        unsigned long long idNode = static_cast<unsigned long long>(query.value(1).toDouble());
        double lat = query.value(2).toDouble();
        double lon = query.value(3).toDouble();
        Node n = Node(idNode,lat,lon);
        nodeVect.emplace_back(n);
        nodeIdVect.emplace_back(idNode);
    }
    Way w = Way(lastId,nodeIdVect,nodeVect);
    roads.emplace_back(w);
    return roads;
}


vector<Way>
DataManager::requestRoadsFromNode(Node node)
{
    //add all the nodes of the result in a vector
    vector<Way> roadsInLat;

    //In this part (until the third while loop) we want to get all the roads that are between two latitudes (wantedLat-0.02 and wantedLat+0.02)
    //Basically, those 2 latitudes can be represented on a map by two horizontal parallels (one 2km above wantedLat and one 2km below)
    uint i = allWays.size()-1;
    Way way = allWays[i]; //allWays is the vector containing every single road that was in the database
    double lat;
    double wantedLat=node.getLatitude();
    uint prev_i=0;
    uint temporaryValue=0;
    uint valueToSubstract;
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
void DataManager::requestRoads()
{
    QSqlQuery query;

    //preparing query
    query.prepare("SELECT id_way,centerLat,centerLon,id_node,latitude,longitude FROM nodes,ways WHERE id_way IN (SELECT id_way FROM nodes, ways WHERE (id_node = node)) and (id_node=node) ORDER BY centerLat,centerLon");

    //execute
    if(!query.exec()){
        qWarning() << "ERROR Finding roads: " << query.lastError().text();
    }


    query.first();
    //add all the nodes of the result in a vector
    vector<Way> roads;
    unsigned long long lastId = static_cast<unsigned long long>(query.value(0).toDouble());
    vector<Node> nodeVect;
    vector<unsigned long long> nodeIdVect;
    Node centerNode;

    while (query.next()) {
        unsigned long long idWay = static_cast<unsigned long long>(query.value(0).toDouble());
        if (idWay != lastId)
        {
            Way w = Way(lastId,nodeIdVect,nodeVect,centerNode);
            roads.emplace_back(w);
            lastId = static_cast<unsigned long long>(query.value(0).toDouble());
            nodeIdVect={};
            nodeVect={};
        }
        unsigned long long idNode = static_cast<unsigned long long>(query.value(3).toDouble());
        double lat = query.value(4).toDouble();
        double lon = query.value(5).toDouble();
        if(lat>=query.value(1).toDouble()-0.00001 && lat<=query.value(1).toDouble()+0.00001 && lon>=query.value(2).toDouble()-0.00001 && lon<=query.value(2).toDouble()+0.00001){ // comparing double with == didn't work
            centerNode=Node(idNode,lat,lon);
        }
        Node n = Node(idNode,lat,lon);
        nodeVect.emplace_back(n);
        nodeIdVect.emplace_back(idNode);
    }
    Way w = Way(lastId,nodeIdVect,nodeVect,centerNode);
    roads.emplace_back(w);
    qDebug() << "Way n°" << roads[0].getId() << "   Center node id: " << roads[0].getCenterNode().getId();
    allWays=roads;
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
        uint l = 0;
        uint nextNode;
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
            for(uint j=0; j<nodes.size(); j++){
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
                        for(uint k=0; k<nodes.size(); k++){
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



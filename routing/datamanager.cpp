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

#include <QCoreApplication>
#include <QDir>
#include <QProcess>
#include <math.h>
#include <utils.h>
#include <QRandomGenerator>

using namespace std;
static bool isDirectionOk;

DataManager::DataManager(QObject *parent) : QObject(parent)
{
    // create the dataBase
    const QString DRIVER("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(DRIVER))                                    //checking the availability of the driver
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);                       //Adding the driver
        db.setDatabaseName("../routing/Data/Database.db");                                  //path for the database    |    do not create a WaysAndNodes.db, it's done automatically

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


Node * DataManager::getNodeFromNodeId(unsigned long long nodeId)
{
    /*
     * Ici, pour parcourir tous les objects node (sachant qu'il y en a énormément), j'utilise la méthode du juste prix:
     * Cela permet par exemple de retrouver un élément dans une liste de 1 000 000 d'éléments en seulement une vingtaine d'opérations.
     */
    //uint i = allNodes.size()-1;
    //    QTime t;
    //    t.start();
    //vector<Node *> localAllNodes = getAllNodes();
    //    globalint+=t.elapsed();
    uint i = allNodes.size()-1;
    Node * node = allNodes[i];
    unsigned long long id;
    unsigned long long prev_i=0;
    unsigned long long temporaryValue=0;
    unsigned long long valueToSubstract;

    while(true){
        node = allNodes[i];
        id =node->getId();
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

//This function stores every roads from the database in a vector of Way
void DataManager::requestRoads(double lat,double lon,double rad)
{
    QCoreApplication::processEvents(QEventLoop::AllEvents);         //display splash screen while loading
    QTime t;
    t.start();
    QSqlQuery query;

    double radNode = rad + 15;               //increasing radius to be sure to have all node from big roads

    //converting
    double minLatNode = lat - radNode/111.11;
    double maxLatNode = lat + radNode/111.11;
    double minLat = lat - rad/111.11;
    double maxLat = lat + rad/111.11;
    double minLonNode,maxLonNode,minLon,maxLon;
    if (lon >= 0)
    {
        minLonNode = lon - radNode/(111.11*cos(lat));           //for longitude radius * cos(latitude) bc 1° =111.11 at ecuador
        maxLonNode = lon + radNode/(111.11*cos(lat));
        minLon = lon - rad/(111.11*cos(lat));
        maxLon = lon + rad/(111.11*cos(lat));
    }
    else {
        minLonNode = lon + radNode/(111.11*cos(lat));
        maxLonNode = lon - radNode/(111.11*cos(lat));
        minLon = lon + rad/(111.11*cos(lat));
        maxLon = lon - rad/(111.11*cos(lat));
    }
    allNodes= createNodeObject(query,minLatNode,maxLatNode,minLonNode,maxLonNode);          //create nodes
    allWays= createWayObject(query,minLat,maxLat,minLon,maxLon);              //create ways
    qDebug() << "Allways size : "<<allWays.size();
    qDebug() << "AllNodes size : "<<allNodes.size();
    qDebug() << "AllNodesAtCrossroads size : "<<allNodesAtCrossroads.size();
    qDebug() << "AllWays & AllNodes creation time: " << t.elapsed() << "ms";

}

vector<Node *> DataManager::createNodeObject(QSqlQuery query,double minLat,double maxLat,double minLon,double maxLon){
    QCoreApplication::processEvents(QEventLoop::AllEvents);                                     //display splash screen while loading
    query.prepare("SELECT DISTINCT id_node,latitude,longitude FROM roads WHERE ((:minLat<=centerLat) and (centerLat<=:maxLat) and (:minLon<=centerLon) and (centerLon<=:maxLon)) ORDER BY id_node");
    query.bindValue(":minLat",minLat);  // this query get all the node with their id,latitude and longitude
    query.bindValue(":maxLat",maxLat);
    query.bindValue(":minLon",minLon);
    query.bindValue(":maxLon",maxLon); // binding all the values

    if(!query.exec()){
        qWarning() << "ERROR Finding roads in RequestRoad: " << query.lastError().text();
    }

    qDebug() << "Query Node finish";
    vector<Node *> nodeVect;
    while (query.next()) {
        unsigned long long idNode = static_cast<unsigned long long>(query.value(0).toDouble());     //get id
        double lat = query.value(1).toDouble();             // get latitude
        double lon = query.value(2).toDouble();             // get longitude
        Node *n = new Node(idNode,lat,lon);                      //create Node
        nodeVect.emplace_back(n);
    }
    qDebug() << "Node created : "<< nodeVect.size();
    return nodeVect;
}

vector<Way *> DataManager::createWayObject(QSqlQuery query,double minLat,double maxLat,double minLon,double maxLon){
    //preparing query
    query.prepare("SELECT DISTINCT id_way,centerLat,centerLon,id_node,oneway,roundabout,maxspeed,type,latitude,longitude FROM roads WHERE ((:minLat<=centerLat) and (centerLat<=:maxLat) and (:minLon<=centerLon) and (centerLon<=:maxLon)) ORDER BY centerLat,id_way");
    query.bindValue(":minLat",minLat);  //This request get all the data from the database within a certain range defined by the radius
    query.bindValue(":maxLat",maxLat);
    query.bindValue(":minLon",minLon);
    query.bindValue(":maxLon",maxLon); // Binding all the values to the SQL query
    QCoreApplication::processEvents(QEventLoop::AllEvents);                                     //display splash screen while loading


    //execute
    if(!query.exec()){
        qWarning() << "ERROR Finding roads in RequestRoad: " << query.lastError().text();
    }

    qDebug() << "Query Ways finish";


    query.first();
    //add all the nodes of the result in a vector
    vector<Node *> wayNodes;              //vector containing all the node in a way
    vector<Way *> wayVector;              //vector containing all the way


    //first iteration is done outside of the while
    unsigned long long lastId = static_cast<unsigned long long>(query.value(0).toDouble());
    Node * centerNode;
    bool oneway = false;                //didn't need to get oneway,roundabout maxspeed and type bc it will only be used in the while()
    bool roundabout = false;
    int maxspeed = 0;
    QString type;
    unsigned long long idNode = static_cast<unsigned long long>(query.value(3).toDouble());     //get the id of the node

    if ((query.value(8).toDouble()-0.00001<query.value(1).toDouble() && query.value(1).toDouble()<query.value(8).toDouble()+0.00001) && (query.value(9).toDouble()-0.00001<query.value(2).toDouble() && query.value(2).toDouble()<query.value(9).toDouble()+0.00001)) //comparaison == impossible with double     //current Node is the CenterNode
    {
        centerNode = getNodeFromNodeId(idNode);                // if the node is in the center of the way
    }

    Node * n = getNodeFromNodeId(idNode);                        // add the first Node
    wayNodes.emplace_back(n);                                           //add to the vector containing all the way
    n->setNumberOfWays(n->getNumberOfWays()+1);

    while (query.next()) {
        unsigned long long idWay = static_cast<unsigned long long>(query.value(0).toDouble());
        if (idWay != lastId)                                                                                    // can't go there without a full circle in the while() bc way are at least 2 node long
        {
            Way *w = new Way(lastId,wayNodes,centerNode,oneway,roundabout,maxspeed,type);                            //creating a way with all the data
            wayVector.emplace_back(w);
            lastId = static_cast<unsigned long long>(query.value(0).toDouble());                                //changing the lastId into the new one
            wayNodes={};                                                                                        //cleaning the vector of node
        }
        unsigned long long idNode = static_cast<unsigned long long>(query.value(3).toDouble());
        oneway = query.value(4).toBool();
        roundabout = query.value(5).toBool();
        maxspeed = query.value(6).toInt();
        QString type = query.value(7).toString();

        if ((query.value(8).toDouble()-0.00001<query.value(1).toDouble() && query.value(1).toDouble()<query.value(8).toDouble()+0.00001) && (query.value(9).toDouble()-0.00001<query.value(2).toDouble() && query.value(2).toDouble()<query.value(9).toDouble()+0.00001)) //comparaison == impossible with double     //current Node is the CenterNode
        {
            centerNode = getNodeFromNodeId(idNode);                            //if centerNode
        }
        Node * n = getNodeFromNodeId(idNode);

        wayNodes.emplace_back(n);
        n->setNumberOfWays(n->getNumberOfWays()+1);
        if(n->getNumberOfWays()==2){
            allNodesAtCrossroads.emplace_back(n);
        }
    }
    Way *w = new Way(lastId,wayNodes,centerNode,oneway,roundabout,maxspeed,type);            // add last way
    wayVector.emplace_back(w);
    for(Way *w:wayVector){
        for(Node *n:w->getNodes()){
            n->addWay(w);
        }
    }
    return wayVector;
}

QVariantList DataManager::requestLatLonFromNodes(QVariant idNode)
{
    QVariantList nodes;
    Node * node = getNodeFromNodeId(static_cast<unsigned long long>(idNode.toDouble()));
    QVariant lat = node->getLatitude();
    QVariant lon = node->getLongitude();
    nodes.append(lat);
    nodes.append(lon);
    return nodes;
}

//vector<Node> DataManager::findRoute()
QVariantList DataManager::findRoute(unsigned long long startNodeId,unsigned long long finishNodeId)
{

    //startNodeId = 38582108; //classique à saint-renan
    //finishNodeId = 1919242171; //resid (croisement)

    QTime t;
    t.start();
    QCoreApplication::processEvents(QEventLoop::AllEvents);                                     //display splash screen while loading


    Node * start = getNodeFromNodeId(startNodeId);
    Node * finish = getNodeFromNodeId(finishNodeId);

    qDebug() << "Route between node n°" << start->getId() << "and node°" << finish->getId();

    start->setDistance(0);
    vector<Node *> aTraiter;
    aTraiter.emplace_back(start);
    vector<Node *> nodesNearby = getNodesNearby(aTraiter[0]);
    bool exit = false;

    //Dijkstra
    //    int j=0;
    while(aTraiter.size()>0){
        unsigned int idMin=0;
        //On regarde quel node est le plus proche du départ
        for(unsigned int i=1;i<aTraiter.size();i++){
            if(aTraiter[i]->getDistance()<aTraiter[idMin]->getDistance()){
                idMin=i;
            }
        }
        Node * currentNode = aTraiter[idMin];
        aTraiter.erase(aTraiter.begin()+int(idMin));
        //On récupère les nodes liés à ce node par une route (On récupère uniquement les Node qui sont des
        //croisements = les Node qui sont communs à plusieurs routes) -> Cela permet d'optimiser le calcul d'itinéraire
        vector<Node *> nodesNearby = getNodesNearby(currentNode);
        currentNode->setMarque(true);

        //        j=j+1;
        //        if (j/10>1){
        //            //reducing frequency of processEvents function
        //            QCoreApplication::processEvents(QEventLoop::AllEvents);                                     //display splash screen while loading
        //            j=0;
        //        }

        for(auto &node: nodesNearby){
            if(node->getMarque()==false){
                //Pour chacun de ces nodes, on regarde si la distance par rapport au départ en passant par
                //currentNode est plus petite que l'ancienne distance par rapport au départ (stockée dans le node).
                if(node->getDistance()>currentNode->getDistance()+distanceBetween(*node,*currentNode)){

                    //                    QCoreApplication::processEvents(QEventLoop::AllEvents);                                     //display splash screen while loading
                    node->setDistance(currentNode->getDistance()+distanceBetween(*node,*currentNode));//Si c'est le cas, on change la distance de ce node par rapport au départ
                    node->setPrecedingNodeId(currentNode->getId());//Et on dit par quel node il faudra passer pour aller au node de départ depuis ce node.
                    node->setMarque(true);
                    aTraiter.emplace_back(node);
                    if(node->getId()==finishNodeId){
                        exit=true;
                    }
                }
            }
        }
    }


    QVariantList nodeList;
    if(exit==true){
        qDebug() << "Noeud de fin atteint";
        //On fait un parcours de l'arrivée au départ (en utilisant à chaque fois precedingNode pour savoir par où passer)
        unsigned long long id = finishNodeId;
        while(id!=startNodeId){

            Node *currentNode =getNodeFromNodeId(id);
            vector<Way *> roadsFromCurrentNode = (currentNode)->getWays();

            unsigned long long precedingNodeId =currentNode->getPrecedingNodeId();
            Node *precedingNode = getNodeFromNodeId(precedingNodeId);
            vector<Way *> roadsFromPrecedingNode = (precedingNode)->getWays();

            //On regarde la route en commun entre les deux Node (currentNode et precedingNode)
            Way *commonWay=roadsFromCurrentNode[0];
            for(uint i=0;i<roadsFromCurrentNode.size();i++) {
                for(uint j=0;j<roadsFromPrecedingNode.size();j++) {
                    if(roadsFromCurrentNode[i]->getId() == roadsFromPrecedingNode[j]->getId()){
                        commonWay=roadsFromCurrentNode[i];
                    }
                }
            }

            //Puis on récupère la position de ces 2 Node dans la route qu'ils ont en commun
            uint pos1 =getPositionInWay(currentNode,commonWay);
            uint pos2 =getPositionInWay(precedingNode,commonWay);

            //Et pour finir on ajoute tous les Node qu'il y a entre ces 2 Node dans la liste à retourner
            //Il faut faire ça car:
            //   - il nous faut tous les nodes pour tracer un itinéraire précis
            //   - l'itinéraire que l'on fait avant est un itinéraire de Node qui sont uniquement des croisements
            vector<Node *> nodesInCommonWay = commonWay->getNodes();
            if(pos1<pos2){
                for (uint i=pos1 ; i<pos2 ; i++) {
                    nodeList.append(nodesInCommonWay[i]->getId());
                }
            }
            else {
                for (uint i=pos1 ; i>pos2 ; i--) {
                    nodeList.append(nodesInCommonWay[i]->getId());
                }
            }

            id=precedingNodeId;
        }
    }
    else {qDebug() << "Noeud de fin pas atteint ...";}
    qDebug() << "Temps pour créer l'itinéraire: " << t.elapsed() << "ms";

    return nodeList;
}

QVariantList DataManager::createRoute(QList<double> startCoord, QVariant km)
{
    QTime t;
    t.start();
    // get the circle
    unsigned long long startNodeId = findClosestNode(startCoord[0],startCoord[1])->getId();                            //1182549307;        //Lanrivoaré

    double radius = km.toDouble()/(2*3.1415);
    qDebug() << radius;
    std::vector<Node *> waypointNodeList = getCircleNode(startNodeId,radius);
    QCoreApplication::processEvents(QEventLoop::AllEvents);         //display splash screen while loading


    bool testLigne = false;                         //enable this if you want to see the circle
    if (testLigne==true){
        QVariantList test;
        for(auto node : waypointNodeList){
            //qDebug()<<node->getId();
            test.append(node->getId());
        }
        qDebug()<<test;
        return test;
    }

    //draw the itinerary
    QVariantList nodeList;
    for(unsigned long i=0;i<waypointNodeList.size()-1;i++){
        QCoreApplication::processEvents(QEventLoop::AllEvents);         //display splash screen while loading
        nodeList.append(findRoute(waypointNodeList[i+1]->getId(),waypointNodeList[i]->getId()));
        qDebug() << "Done : " <<i+1<<"/"<<waypointNodeList.size()-1;
        for(auto node : allNodesAtCrossroads){
            node->setMarque(0);
            node->setDistance(100000);
        }
    }


    //    nodeList.append(findRoute(waypointNodeList[4]->getId(),waypointNodeList[3]->getId()));
    //    for(auto node : allNodesAtCrossroads){
    //        node->setMarque(0);
    //        node->setDistance(100000);
    //    }

    //qDebug()<<nodeList;
    QTime chrono = QTime::currentTime();
    bool verifOk = false;
    qDebug()<<"size of nodeList :" << nodeList.size();
    while(!verifOk){
        verifOk = verifList(&nodeList);
    }
    QTime endChrono = QTime::currentTime();
    qDebug() << "Chrono verifying roads : " << chrono.msecsTo(endChrono);           //qq ms -> Pas nécessaire d'optimiser pour l'instant
    qDebug() << "size of nodeList :" << nodeList.size();
    double itinerarylength = getItineraryLength(nodeList);
    qDebug() << "Longueur de l'itinéraire : " << itinerarylength ;
    qDebug() << "Temps total pour créer l'itinéraire : " << t.elapsed() << "ms";
    if(itinerarylength>=(km.toDouble()*1.2) || itinerarylength<=(km.toDouble()*0.8)){
        nodeList=createRoute(startCoord,km);
    }
    qDebug() << "Temps total pour créer l'itinéraire : " << t.elapsed() << "ms";
    return nodeList;
}

QVariantList DataManager::createItinerary(QList<double> startCoord, QList<double> finishCoord){
    QTime t;
    t.start();
    // get the circle
    unsigned long long startNodeId = findClosestNode(startCoord[0],startCoord[1])->getId();
    unsigned long long finishNodeId = findClosestNode(finishCoord[0],finishCoord[1])->getId();//1182549307;        //Lanrivoaré

    //draw the itinerary
    QVariantList nodeList;
    QCoreApplication::processEvents(QEventLoop::AllEvents);         //display splash screen while loading
    nodeList.append(findRoute(startNodeId,finishNodeId));
    for(auto node : allNodesAtCrossroads){
        node->setMarque(0);
        node->setDistance(100000);
    }

    //qDebug()<<nodeList;
    QTime chrono = QTime::currentTime();
    bool verifOk = false;
    qDebug()<<"size of nodeList :" << nodeList.size();
    while(!verifOk){
        verifOk = verifList(&nodeList);
    }
    QTime endChrono = QTime::currentTime();
    qDebug() << "Chrono verifying roads : " << chrono.msecsTo(endChrono);           //qq ms -> Pas nécessaire d'optimiser pour l'instant
    qDebug() << "size of nodeList :" << nodeList.size();
    qDebug() << "Longueur de l'itinéraire : " << getItineraryLength(nodeList);
    qDebug() << "Temps total pour créer l'itinéraire : " << t.elapsed() << "ms";
    return nodeList;
}

std::vector<Node *> DataManager::getCircleNode(unsigned long long startNodeId,double radius){
    int pointsNumber =4;
    double angleBetween = 360/pointsNumber;
    double startAngle;
    Node * centerNode;
    int direction;
    QVariantList waypointList;
    isDirectionOk = false;

    while (isDirectionOk==false){
        waypointList.clear();   //clear the list
        isDirectionOk = true;  //reset for another  test

        int maxValue = 360;
        direction = int(QRandomGenerator::global()->generateDouble()*maxValue);
        qDebug() << "direction : " << direction;

        startAngle = direction-180;
        //set startAngle (180 - angle of direction)
        /* un depart vers l'est, implique un point de depart a gauche du cercle
         * on commence donc par ce point*/

        centerNode = getCircleCenter(radius,direction,startNodeId);

        //get Node for every waypoint
        for(int i=0;i<pointsNumber;i++){
            QVariantList coord;

            //qDebug() << startAngle+angleBetween*i;
            coord = addKmWithAngle(centerNode,startAngle+angleBetween*i,radius);
            Node * waypoint = findClosestNode(coord[0].toDouble(),coord[1].toDouble());
            waypointList.append(waypoint->getId());
        }

        qDebug() <<"Is direction ok ? : "<< isDirectionOk;
    }
    isDirectionOk = true;

    QVariantList coord;
    coord = addKmWithAngle(centerNode,startAngle,radius);

    Node * waypoint = findClosestNode(coord[0].toDouble(),coord[1].toDouble());
    waypointList.append(waypoint->getId());            // adding startNode to close the route

    std::vector<Node *> waypointNodeList;
    //create a vector of node from a vector of id
    for(auto waypnt : waypointList){

        waypointNodeList.emplace_back(getNodeFromNodeId(static_cast<unsigned long long>(waypnt.toDouble())));

    }
    //qDebug() << waypointNodeList;
    return waypointNodeList;
}

bool DataManager::verifList(QVariantList *nodeList){
    QVariantList localNode = *nodeList;
    for(int i=1;i<localNode.size()-1;i++){
        if(localNode[i-1] == localNode[i+1]){         //verifie si il y a un noeud puis demi-tour
            localNode.removeAt(i);
        }
    }
    bool isVerified = false;
    while(isVerified==false){
        isVerified = true;
        for(int i=1;i<localNode.size();i++){
            QVariant currentValue = localNode[i];
            if(localNode[i-1] == localNode[i]){               //verifie si il y a 2 noeuds successifs
                localNode.removeAt(i);
                localNode.removeAt(i-1);
                isVerified = false;                     // au moins un point a été enlever, on verifie toute la liste pour etre sur

                if(localNode[i-1]!=localNode[i-2]){               // les noeuds sont differents, on va sortir de la boucle
                    bool flag = false;                              //permet de break dans un double for
                    int lowIndex = 0;
                    int highIndex = 0;
                    bool detection = false;
                    for(int j=0;j<30;j++) {
                        for(int k=0;k<30;k++){
                            if(localNode[i-2-j]==localNode[i+k]){   //on cherche un point commun dans les noeuds suivant pour etre sur d'eviter les "terre plein"
                                lowIndex =i-2-j;
                                highIndex = i+k;
                                flag = true;
                                detection = true;
                                break;
                            }
                        }
                        if(flag==true){break;}
                    }
                    if (detection==true){               //si un terre plein est détécté, on enleve les points des deux coté de la liste
                        std::vector<int> range;
                        for (int removeIndex = lowIndex; removeIndex < highIndex; removeIndex++) {
                            range.emplace_back(removeIndex);
                        }
                        for (int removeIndex2 = 0; removeIndex2 < highIndex-lowIndex; ++removeIndex2) {
                            localNode.removeAt(lowIndex);
                        }
                        *nodeList = localNode;                  //on stocke dans le vecteur de retour la liste courante. en envoyant false on demande au programme de relancer la verification
                        return false;
                    }else {
                        localNode.insert(i-1,currentValue);          // si aucune séparation est détéctée, a la fin de la suppression on ajoute le dernier noeud retiré pour combler le manque
                    }
                }
            }
        }
    }
    *nodeList = localNode;
    return true;
}

Node *DataManager::getCircleCenter(double radius, int direction, unsigned long long startNodeId)
{
    //this function returns the center of a tangent circle as a function of direction
    Node * startNode = getNodeFromNodeId(startNodeId);

    QVariantList returnValue = addKmWithAngle(startNode,direction,radius);
    QVariantList coord;
    Node * n = new Node(0,returnValue[0].toDouble(),returnValue[1].toDouble());
    return n;        //return the closest node from the coordinate
}

vector<Node *> DataManager::getNodesNearby(Node * node)
{
    vector<Node *> nodesNearby;
    vector<Way *> ways = (node)->getWays();
    while(!ways.empty()){
        Way *currentWay = ways[ways.size()-1];
        vector<Node *> nodes = currentWay->getNodes();
        uint i = getPositionInWay(node,currentWay);
        while(i<nodes.size()-1){
            i++;
            if(nodes[i]->getNumberOfWays()>1){
                nodesNearby.emplace_back(nodes[i]);
                break;
            }
        }
        i = getPositionInWay(node,currentWay);
        while(true){
            if(i==0){break;}
            i--;
            if(nodes[i]->getNumberOfWays()>1){
                nodesNearby.emplace_back(nodes[i]);
                break;
            }
        }
        ways.pop_back();
    }
    return nodesNearby;
}

Node * DataManager::findClosestNode(double latitude,double longitude){
    std::vector<Node *> nodes = allNodesAtCrossroads;
    Node target = Node(1,latitude,longitude);
    double bestDistance = 100000;
    Node * bestNode;
    for(auto node : nodes){                                     //find best node (WIP : and best node without tertiary way)
        double newDistance = distanceBetween(target,*node);
        if(newDistance<bestDistance){                           //check every node to get the closer one
            bestDistance = newDistance;
            bestNode = node;
        }
    }
//    qDebug() << "Best Distance : "<<bestDistance;
    if (bestDistance>3){
        isDirectionOk = false;
    }
    return bestNode;
}

bool DataManager::extendDatabase(QStringList departement){
    QDir dir = QDir::currentPath();     //return path in the build folder
    dir.cdUp();                         //project folder
    dir.cd("routing");                  //routing folder

    QString program("python");
    QStringList filepath = QStringList()<< dir.path()+"/generateTiles.py";         //on récupére le path du fichier à éxécuter
    QStringList args = QStringList()<<filepath<<departement;                             //création de la ligne de commande qui sera envoyée
    //    qDebug()<<args;
    QProcess p;
    p.setWorkingDirectory(dir.path());
    //qDebug() << "args : " << args << "\n dir.path : " << dir.path();
    p.execute(program, args);
    return true;
}

double DataManager::getItineraryLength(QVariantList routeNodes)
{
    double itineraryLength = 0;
    qDebug() << "1" << routeNodes.size();
    for(int i=0; i<routeNodes.size()-1; ++i){
        unsigned long long nodeA = static_cast<unsigned long long>(routeNodes[i].toDouble());
        unsigned long long nodeB = static_cast<unsigned long long>(routeNodes[i+1].toDouble());
        itineraryLength+=distanceBetween(*getNodeFromNodeId(nodeA),*getNodeFromNodeId(nodeB));
    }
    return itineraryLength;
}

double DataManager::distanceBetween(Node A, Node B)
{
    int r=6371; //earth radius in km
    double latA = A.getLatitude()*M_PI/180;
    double lonA = A.getLongitude()*M_PI/180;
    double latB = B.getLatitude()*M_PI/180;
    double lonB = B.getLongitude()*M_PI/180;

    double a = sin((latB-latA)/2)*sin((latB-latA)/2) + cos(latA)*cos(latB)*sin((lonB-lonA)/2)*sin((lonB-lonA)/2);
    double c = 2*atan2(sqrt(a),sqrt(1-a));
    double distance = r*c;

    return distance;
}

double DataManager::bearingBetween(Node A, Node B)
{
    double latA = A.getLatitude()*M_PI/180;
    double lonA = A.getLongitude()*M_PI/180;
    double latB = B.getLatitude()*M_PI/180;
    double lonB = B.getLongitude()*M_PI/180;
    double bearing = atan2(sin((lonB-lonA))*cos(latB), cos(latA)*sin(latB)-sin(latA)*cos(latB)*cos((lonB-lonA)));
    return bearing*180/M_PI;
}

bool DataManager::addNodes(QVariantList &routeNodes, unsigned long long finishNodeId)
{
    bool finishNodeIsHere = false;
    return finishNodeIsHere;
}

uint DataManager::getPositionInWay(Node *n, Way *way)
{
    vector<Node *> nodes = way->getNodes();
    unsigned long long wantedId = n->getId();
    if(nodes[0]->getId() == wantedId){return 0;}
    else if (nodes[nodes.size()-1]->getId() == wantedId) {return nodes.size()-1;}
    else{
        for(uint i=0;i<nodes.size()-1;i++){
            if(nodes[i]->getId() == wantedId){return i;}
        }
    }
}

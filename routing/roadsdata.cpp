#include "roadsdata.h"

#include <QJsonArray>


RoadsData::RoadsData(QObject *parent) : QObject (parent)
{

}

void RoadsData::generateWaysAndNodes(QJsonObject allRoads, DataManager db)
{
    vector<Way> wayObjectVector;    //A vector that contains every Way objects
    vector<Node> nodeObjectVector;  //A vector that contains every Node objects

    int length = allRoads["elements"].toArray().size(); //allRoads["elements"] contains all the ways and nodes (in JSON)
    for (int i=0;i<length;i++) {
        //for Qt 5.9
        QJsonObject element = allRoads["elements"].toArray()[i].toObject();

        //for Qt 5.10
        //QJsonValue element = QJsonValue(allRoads["elements"])[i]; //contains one way OR one node (with everything that's inside it), (in JSON)
        if(element["type"]=="node"){
            uint64_t nodeId = static_cast<uint64_t>(element["id"].toDouble()); //it has to be uint64_t because the Id can be more than 2^32 (so uint_32_t and below won't work)
            double latitude = element["lat"].toDouble();
            double longitude = element["lon"].toDouble();
            Node node = Node(nodeId,latitude,longitude); //create an object Node with the 3 parameters from above
            nodeObjectVector.emplace_back(node);
        }
        else if(element["type"]=="way"){
            vector<uint64_t> nodeIdVector;                                //A vector that contains all the Node objects' Id of one object Way
            vector<Node> nodeVector;                                     //A vector that contains all the Node objects of one object Way
            uint64_t id = static_cast<uint64_t>(element["id"].toDouble()); //get the id in uint64_t (same reason as above)
            QJsonArray nodeArray = element["nodes"].toArray();            //nodsArray contains all the node from one way (in JSON)
            for(auto node : nodeArray)
            {
                uint64_t nodeId = static_cast<uint64_t>(node.toDouble());
                nodeIdVector.emplace_back(nodeId);
//                Node wayNode = getNodeFromNodeId(nodeId, nodeObjectVector); //returns the object Node that correspond to the given nodeId
//                nodeVector.emplace_back(wayNode);
//                qDebug() << "Stuck ?";
            }
            if (nodeIdVector.size()!=0) //security
            {
                Way w = Way(id,nodeIdVector); //creating the way with the parameters from above
                wayObjectVector.emplace_back(w);
            }
        }
    }
    db.addValuesWays(wayObjectVector);
    db.addValuesNodes(nodeObjectVector);

    //qDebug() << "\nAmount of nodes: " << nodeObjectVector.size();;
}

Node RoadsData::getNodeFromNodeId(uint64_t nodeId, vector<Node> &nodeObjectVector)
{
    /*
     * Ici, pour parcourir tous les objects node (sachant qu'il y en a énormément), j'utilise la méthode du juste prix:
     * Cela permet par exemple de retrouver un élément dans une liste de 1 000 000 d'éléments en seulement une vingtaine d'opérations.
     */
    uint i = nodeObjectVector.size()-1;
    Node node = nodeObjectVector[i];
    uint64_t id;
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

vector<Way> RoadsData::getWayVector() const
{
    return wayVector;
}

QVariantList RoadsData::findRouteFrom(double lat, double lon)
{
    return myDb.findRouteFrom(lat,lon);
}

QVariantList RoadsData::requestLatLonFromNodes(QVariant idNode)
{
    return myDb.requestLatLonFromNodes(idNode);
}



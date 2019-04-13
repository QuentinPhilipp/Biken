#include <QApplication>


#include <string>
#include <QDebug>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

#include "Nodes.h"
#include "Ways.h"
#include "requetesapi.h"

using namespace std;


vector<Ways> generateWaysAndNodes(QJsonObject allRoads);
Nodes getNodeFromNodeId(uint64_t nodeId, uint nbNodes, vector<Nodes> &nodesObjectVector);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //make a request to get all the roads around a coordinate
    RequetesAPI *requeteRoads = new RequetesAPI();
    QString radius = "100000"; //radius in meters
    QJsonObject allRoads = requeteRoads->getAllRoadsAroundThePoint("48.434420","-4.640103",radius);


    //store all the roads and nodes in differents classes.
    vector<Ways> waysVector = generateWaysAndNodes(allRoads);

    //Verification
    uint size = waysVector.size();
    qDebug() << "\nAmount of ways: " << size ;
    waysVector[size-1].displayGPSData();
    qDebug() << "\n~~~~ Finished ! ~~~~";

    return a.exec();
}


//This function is used to transform JsonValues array to differents classes define in the files 'Nodes.cpp' and 'Ways.cpp'
vector<Ways> generateWaysAndNodes(QJsonObject allRoads){
    vector<Ways> waysObjectVector;    //A vector that contains every Ways objects
    vector<Nodes> nodesObjectVector;  //A vector that contains every Nodes objects
    uint nbNodes=0;

    int length = allRoads["elements"].toArray().size(); //allRoads["elements"] contains all the ways and nodes (in JSON)
    for (int i=0;i<length;i++) {
        QJsonValue element = QJsonValue(allRoads["elements"])[i]; //contains one way OR one node (with everything that's inside it), (in JSON)
        if(element["type"]=="node"){
            uint64_t nodeId = static_cast<uint64_t>(element["id"].toDouble()); //it has to be uint64_t because the Id can be more than 2^32 (so uint_32_t and below won't work)
            double latitude = element["lat"].toDouble();
            double longitude = element["lon"].toDouble();
            Nodes node = Nodes(nodeId,latitude,longitude); //create an object Nodes with the 3 parameters from above
            nodesObjectVector.emplace_back(node);
            nbNodes++;
        }
        else if(element["type"]=="way"){
            vector<uint64_t> nodesIdVector;                                //A vector that contains all the Nodes' Id of one object Ways
            vector<Nodes> nodesVector;                                     //A vector that contains all the Nodes of one object Ways
            uint64_t id = static_cast<uint64_t>(element["id"].toDouble()); //get the id in uint64_t (same reason as above)
            QJsonArray nodesArray = element["nodes"].toArray();            //nodesArray contains all the nodes from one way (in JSON)
            for(auto node : nodesArray)
            {
                uint64_t nodeId = static_cast<uint64_t>(node.toDouble());
                nodesIdVector.emplace_back(nodeId);
                Nodes wayNode = getNodeFromNodeId(nodeId,nbNodes, nodesObjectVector); //returns the object Nodes that correspond to the given nodeId
                nodesVector.emplace_back(wayNode);
            }
            if (nodesIdVector.size()!=0) //security
            {
                Ways w = Ways(id,nodesIdVector,nodesVector); //creating the way with the parameters from above
                waysObjectVector.emplace_back(w);
            }
        }
    }
    qDebug() << "Roads are stored in the classes. OK ! ";
    qDebug() << "\nAmount of nodes: " << nodesObjectVector.size();

    return waysObjectVector;
}


Nodes getNodeFromNodeId(uint64_t nodeId, uint nbNodes, vector<Nodes> &nodesObjectVector){
    /*
     * Ici, pour parcourir tous les nodes (sachant qu'il y en a énormément), j'utilise la méthode du juste prix:
     * Cela permet par exemple de retrouver un élément dans une liste de 1 000 000 d'éléments en seulement une vingtaine d'opérations.
     */
    uint i = nbNodes-1;
    Nodes node = nodesObjectVector[i];
    uint64_t id;
    uint prev_i=0;
    uint temporaryValue=0;
    uint valueToSubstract;
    while(true){
        node = nodesObjectVector[i];
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

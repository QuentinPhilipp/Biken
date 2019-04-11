#include <QApplication>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <string>
#include <QByteArray>
#include <QEvent>
#include <QDebug>
#include <QObject>
#include "Nodes.h"
#include "Ways.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

//using qDebug to print in the Qt console



//This function is used to transform JsonValues array to differents classes define in the files 'Nodes.cpp' and 'Ways.cpp'
std::tuple<std::vector<Nodes>,std::vector<Ways>> generateWaysAndNodes(std::vector<QJsonValue> ways,std::vector<QJsonValue> nodes){
    //transform nodes in nodeObject
    std::vector<Nodes> nodesObjectVector;                                       //store all node object in a vector
    for(auto node : nodes){
        QJsonObject value = node.toObject();
        std::string id = std::to_string(value["id"].toInt());                   //get the id
        double latitude = value["lat"].toDouble();                              //get latitude
        double longitude = value["lon"].toDouble();                             //get longitude
        Nodes n = Nodes(id,latitude,longitude);
        nodesObjectVector.emplace_back(n);
    }
    qDebug() << "All nodes transformed";
//    qDebug() << nodesObjectVector.size();

    //transform ways in wayObject and add the node in it
    std::vector<Ways> waysObjectVector;                                         //store all ways object in a vector
    for(auto way : ways)
    {
        std::vector<Nodes> nodesWaysVector;                                     //store all the nodes that go in this way
        QJsonObject value = way.toObject();
        std::string id = std::to_string(value["id"].toInt());                   //get the id in string
        QJsonArray nodesArray = value["nodes"].toArray();
        for(auto node : nodesArray)
        {
            std::string nodeId = std::to_string(node.toInt());
            for(auto nodeObject : nodesObjectVector)
            {
               if (nodeObject.getId()==nodeId)
               {nodesWaysVector.emplace_back(nodeObject);}                      //emplace back the node in the vector that store all the node of this way
            }
        }
        if (nodesWaysVector.size()!=0)                                          //security
        {
            Ways w = Ways(id,nodesWaysVector);                                  //creating the way
            waysObjectVector.emplace_back(w);                                   //emplace back in the ways vector
        }
    }
    qDebug() << "All ways transformed";
//    qDebug() << waysObjectVector.size();
//    qDebug() << "counter of referencies : "<< counter;
//    waysObjectVector[0].displayGPSData();
    qDebug() << "Roads are stored in the classes. OK ! ";

    return {nodesObjectVector,waysObjectVector};
    }


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString latitude = "48.434420";
    QString longitude = "-4.640103";
    QString radius = "1000"; //in meter
    QString urlString = "http://overpass-api.de/api/interpreter?data=%3Cosm-script%20output%3D%22json"
            "%22%3E%0A%20%20%3Cquery%20type%3D%22way"
            "%22%3E%0A%20%20%20%20%20%20%3C"
            "around%20lat%3D%22"+latitude+
            "%22%20lon%3D%22"+longitude+
            "%22%20radius%3D%22"+radius+
            "%22%2F%3E%0A%20%20%20%20%20%20%3Chas-kv%20k%3D%22highway"
            //here we set the roads we want (motorway,trunk,primary,secondary,tertiary,unclassified,residential)
            "%22%20regv%3D%22primary%7Csecondary%7Ctertiary%7C"
            "%22%2F%3E%0A%20%20%3C%2Fquery%3E%0A%20%20%3Cunion%3E%0A%20%20%20%20%3Citem%2F%3E%0A%20%20%20%20%3"
            "Crecurse%20type%3D%22down%22%2F%3E%0A%20%20%3C%2Funion%3E%0A%20%20%3Cprint%2F%3E%0A%3C%2Fosm-script%3E";
    QUrl url(urlString);
    QNetworkRequest request(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager();

    //In this part, we create a loop that runs until the QNetworkReply has finished processing.
    QEventLoop loop;
    QObject::connect(manager,
                     SIGNAL(finished(QNetworkReply*)), //finished is a signal from the QNetworkReply Class that is emitted when the reply has finished processing.
                     &loop,
                     SLOT(quit())); //slot from QEventLoop that calls exit()
    QNetworkReply* reply = manager->get(request);
    loop.exec(); //enters the loop and stays in it until loop.exit() is called


    //Put the reply in JSON
    if(reply->error() == QNetworkReply::NoError)
    {
        std::vector<QJsonValue> nodes;
        std::vector<QJsonValue> ways;
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["elements"].toArray();


        //Put all the nodes in a vector and all the ways in another
        for (auto elem : jsonArray)
        {
            QJsonValue value = elem;
            QJsonObject item = value.toObject();
            QJsonValue val = item["type"];
            if (val=="node") {nodes.emplace_back(elem);}
            else {ways.emplace_back(elem);}
        }
        //store all the roads and nodes in differents classes.
        auto [nodeVector,waysVector] = generateWaysAndNodes(ways,nodes);

        //Examples
        waysVector[0].displayGPSData();


    }

    manager->~QNetworkAccessManager();
    return a.exec();
}

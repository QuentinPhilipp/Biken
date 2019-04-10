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

std::tuple<std::vector<Nodes>,std::vector<Ways>> generateWaysAndNodes(std::vector<QJsonValue> ways,std::vector<QJsonValue> nodes){
    //transfromer les nodes en object node
    std::vector<Nodes> nodesObjectVector;
    for(auto node : nodes){
        QJsonObject value = node.toObject();
        std::string id = std::to_string(value["id"].toInt());
        double latitude = value["lat"].toDouble();
        double longitude = value["lon"].toDouble();
        Nodes n = Nodes(id,latitude,longitude);
        nodesObjectVector.emplace_back(n);
    }
    qDebug() << "All nodes transformed";
//    qDebug() << nodesObjectVector.size();


    //transformer les ways en Objets de type ways
    //et y ajouter les nodes
    std::vector<Ways> waysObjectVector;
    int counter =0;
    for(auto way : ways)
    {
        std::vector<Nodes> nodesWaysVector;
        QJsonObject value = way.toObject();
        std::string id = std::to_string(value["id"].toInt());
        QJsonArray nodesArray = value["nodes"].toArray();
        for(auto node : nodesArray)
        {
            std::string nodeId = std::to_string(node.toInt());
            for(auto nodeObject : nodesObjectVector)
            {
                //qDebug() <<"nodeObject id : " << atoi(nodeObject.getId().c_str());
                //qDebug() <<"nodeId : "<<atoi(nodeId.c_str());
               if (nodeObject.getId()==nodeId)
               {
                    nodesWaysVector.emplace_back(nodeObject);
                    //qDebug() << "\n\n\n\nMATCH\n\n\n\n";
                    counter+=1;
               }
            }
        }
        if (nodesWaysVector.size()!=0)
        {
            Ways w = Ways(id,nodesWaysVector);
            waysObjectVector.emplace_back(w);
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
    QUrl url("http://overpass-api.de/api/interpreter?data=%3Cosm-script%20output%3D%22json%22%3E%0A%20%20%3Cquery%20type%3D%22way%22%3E%0A%20%20%20%20%20%20%3Caround%20lat%3D%2248.434420%22%20lon%3D%22-4.640103%22%20radius%3D%221000%22%2F%3E%0A%20%20%20%20%20%20%3Chas-kv%20k%3D%22highway%22%20regv%3D%22tertiary%7Cprimary%7Csecondary%22%2F%3E%0A%20%20%3C%2Fquery%3E%0A%20%20%3Cunion%3E%0A%20%20%20%20%3Citem%2F%3E%0A%20%20%20%20%3Crecurse%20type%3D%22down%22%2F%3E%0A%20%20%3C%2Funion%3E%0A%20%20%3Cprint%2F%3E%0A%3C%2Fosm-script%3E");
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



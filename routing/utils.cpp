#include "utils.h"


double addKmToLongitude(double lon,double lat,double km)                // if km>0, adding km to the east
{
//    qDebug() << "longitude entrée : "<< lon << lat;
    double longitude = lon + km/(111.11*qCos(qDegreesToRadians(lat)));           //for longitude radius * cos(latitude) bc 1° =111.11 at ecuador
//    qDebug() << "longitude entrée : "<< longitude;
    return longitude;
}

double addKmToLatitude(double lat,double km)                             // if km>0, adding km to the north
{
    double latitude = lat + km/111.11;
    return latitude;
}

QVariantList addKmWithAngle(Node* center,double angle,double radius){           //angles basés sur repere trigo
    QVariantList returnValues;
    double startLat = center->getLatitude();
    double startLon = center->getLongitude();

    double addLat,addLon;

    addLat = qSin(qDegreesToRadians(angle))*radius;
    addLon = qCos(qDegreesToRadians(angle))*radius;

    returnValues.append(addKmToLatitude(startLat,addLat));
    returnValues.append(addKmToLongitude(startLon,startLat,addLon));

    return returnValues;
}

#ifndef UTILS_H
#define UTILS_H

#include <QVariant>
#include <QtMath>
#include "node.h"
#include <QDebug>
#include <QVariantList>




double addKmToLongitude(double lon,double lat,double km);
double addKmToLatitude(double lat,double km);
QVariantList addKmWithAngle(Node* center,double angle,double radius);

#endif // UTILS_H

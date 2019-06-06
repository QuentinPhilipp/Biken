/****************************************************************************
** Meta object code from reading C++ file 'datamanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../routing/datamanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datamanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataManager_t {
    QByteArrayData data[20];
    char stringdata0[243];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataManager_t qt_meta_stringdata_DataManager = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DataManager"
QT_MOC_LITERAL(1, 12, 22), // "requestLatLonFromNodes"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 6), // "idNode"
QT_MOC_LITERAL(4, 43, 9), // "findRoute"
QT_MOC_LITERAL(5, 53, 11), // "startNodeId"
QT_MOC_LITERAL(6, 65, 12), // "finishNodeId"
QT_MOC_LITERAL(7, 78, 13), // "getCircleNode"
QT_MOC_LITERAL(8, 92, 18), // "std::vector<Node*>"
QT_MOC_LITERAL(9, 111, 6), // "radius"
QT_MOC_LITERAL(10, 118, 11), // "createRoute"
QT_MOC_LITERAL(11, 130, 13), // "QList<double>"
QT_MOC_LITERAL(12, 144, 10), // "startCoord"
QT_MOC_LITERAL(13, 155, 2), // "km"
QT_MOC_LITERAL(14, 158, 15), // "createItinerary"
QT_MOC_LITERAL(15, 174, 11), // "finishCoord"
QT_MOC_LITERAL(16, 186, 14), // "extendDatabase"
QT_MOC_LITERAL(17, 201, 11), // "departement"
QT_MOC_LITERAL(18, 213, 18), // "getItineraryLength"
QT_MOC_LITERAL(19, 232, 10) // "routeNodes"

    },
    "DataManager\0requestLatLonFromNodes\0\0"
    "idNode\0findRoute\0startNodeId\0finishNodeId\0"
    "getCircleNode\0std::vector<Node*>\0"
    "radius\0createRoute\0QList<double>\0"
    "startCoord\0km\0createItinerary\0finishCoord\0"
    "extendDatabase\0departement\0"
    "getItineraryLength\0routeNodes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x02 /* Public */,
       4,    2,   52,    2, 0x02 /* Public */,
       7,    2,   57,    2, 0x02 /* Public */,
      10,    2,   62,    2, 0x02 /* Public */,
      14,    2,   67,    2, 0x02 /* Public */,
      16,    1,   72,    2, 0x02 /* Public */,
      18,    1,   75,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::QVariantList, QMetaType::QVariant,    3,
    QMetaType::QVariantList, QMetaType::ULongLong, QMetaType::ULongLong,    5,    6,
    0x80000000 | 8, QMetaType::ULongLong, QMetaType::Double,    5,    9,
    QMetaType::QVariantList, 0x80000000 | 11, QMetaType::QVariant,   12,   13,
    QMetaType::QVariantList, 0x80000000 | 11, 0x80000000 | 11,   12,   15,
    QMetaType::Bool, QMetaType::QStringList,   17,
    QMetaType::Int, QMetaType::QVariantList,   19,

       0        // eod
};

void DataManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QVariantList _r = _t->requestLatLonFromNodes((*reinterpret_cast< QVariant(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 1: { QVariantList _r = _t->findRoute((*reinterpret_cast< unsigned long long(*)>(_a[1])),(*reinterpret_cast< unsigned long long(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 2: { std::vector<Node*> _r = _t->getCircleNode((*reinterpret_cast< unsigned long long(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< std::vector<Node*>*>(_a[0]) = std::move(_r); }  break;
        case 3: { QVariantList _r = _t->createRoute((*reinterpret_cast< QList<double>(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 4: { QVariantList _r = _t->createItinerary((*reinterpret_cast< QList<double>(*)>(_a[1])),(*reinterpret_cast< QList<double>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->extendDatabase((*reinterpret_cast< QStringList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { int _r = _t->getItineraryLength((*reinterpret_cast< QVariantList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<double> >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<double> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DataManager.data,
    qt_meta_data_DataManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DataManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

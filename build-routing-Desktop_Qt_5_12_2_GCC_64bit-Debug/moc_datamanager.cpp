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
    QByteArrayData data[21];
    char stringdata0[233];
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
QT_MOC_LITERAL(4, 43, 13), // "findRouteFrom"
QT_MOC_LITERAL(5, 57, 3), // "lat"
QT_MOC_LITERAL(6, 61, 3), // "lon"
QT_MOC_LITERAL(7, 65, 9), // "findRoute"
QT_MOC_LITERAL(8, 75, 11), // "startNodeId"
QT_MOC_LITERAL(9, 87, 12), // "finishNodeId"
QT_MOC_LITERAL(10, 100, 13), // "getCircleNode"
QT_MOC_LITERAL(11, 114, 18), // "std::vector<Node*>"
QT_MOC_LITERAL(12, 133, 9), // "direction"
QT_MOC_LITERAL(13, 143, 6), // "radius"
QT_MOC_LITERAL(14, 150, 15), // "createItinerary"
QT_MOC_LITERAL(15, 166, 13), // "QList<double>"
QT_MOC_LITERAL(16, 180, 10), // "startCoord"
QT_MOC_LITERAL(17, 191, 11), // "finishCoord"
QT_MOC_LITERAL(18, 203, 2), // "km"
QT_MOC_LITERAL(19, 206, 14), // "extendDatabase"
QT_MOC_LITERAL(20, 221, 11) // "departement"

    },
    "DataManager\0requestLatLonFromNodes\0\0"
    "idNode\0findRouteFrom\0lat\0lon\0findRoute\0"
    "startNodeId\0finishNodeId\0getCircleNode\0"
    "std::vector<Node*>\0direction\0radius\0"
    "createItinerary\0QList<double>\0startCoord\0"
    "finishCoord\0km\0extendDatabase\0departement"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x02 /* Public */,
       4,    2,   47,    2, 0x02 /* Public */,
       7,    2,   52,    2, 0x02 /* Public */,
      10,    3,   57,    2, 0x02 /* Public */,
      14,    3,   64,    2, 0x02 /* Public */,
      19,    1,   71,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::QVariantList, QMetaType::QVariant,    3,
    QMetaType::QVariantList, QMetaType::Double, QMetaType::Double,    5,    6,
    QMetaType::QVariantList, QMetaType::ULongLong, QMetaType::ULongLong,    8,    9,
    0x80000000 | 11, QMetaType::ULongLong, QMetaType::Int, QMetaType::Double,    8,   12,   13,
    QMetaType::QVariantList, 0x80000000 | 15, 0x80000000 | 15, QMetaType::QVariant,   16,   17,   18,
    QMetaType::Bool, QMetaType::QStringList,   20,

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
        case 1: { QVariantList _r = _t->findRouteFrom((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 2: { QVariantList _r = _t->findRoute((*reinterpret_cast< unsigned long long(*)>(_a[1])),(*reinterpret_cast< unsigned long long(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 3: { std::vector<Node*> _r = _t->getCircleNode((*reinterpret_cast< unsigned long long(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< std::vector<Node*>*>(_a[0]) = std::move(_r); }  break;
        case 4: { QVariantList _r = _t->createItinerary((*reinterpret_cast< QList<double>(*)>(_a[1])),(*reinterpret_cast< QList<double>(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->extendDatabase((*reinterpret_cast< QStringList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

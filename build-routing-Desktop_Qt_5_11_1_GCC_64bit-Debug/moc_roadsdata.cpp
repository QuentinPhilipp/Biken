/****************************************************************************
** Meta object code from reading C++ file 'roadsdata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../routing/roadsdata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'roadsdata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RoadsData_t {
    QByteArrayData data[7];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RoadsData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RoadsData_t qt_meta_stringdata_RoadsData = {
    {
QT_MOC_LITERAL(0, 0, 9), // "RoadsData"
QT_MOC_LITERAL(1, 10, 13), // "findRouteFrom"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 3), // "lat"
QT_MOC_LITERAL(4, 29, 3), // "lon"
QT_MOC_LITERAL(5, 33, 22), // "requestLatLonFromNodes"
QT_MOC_LITERAL(6, 56, 6) // "idNode"

    },
    "RoadsData\0findRouteFrom\0\0lat\0lon\0"
    "requestLatLonFromNodes\0idNode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RoadsData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x02 /* Public */,
       5,    1,   29,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::QVariantList, QMetaType::Double, QMetaType::Double,    3,    4,
    QMetaType::QVariantList, QMetaType::QVariant,    6,

       0        // eod
};

void RoadsData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RoadsData *_t = static_cast<RoadsData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QVariantList _r = _t->findRouteFrom((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 1: { QVariantList _r = _t->requestLatLonFromNodes((*reinterpret_cast< QVariant(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RoadsData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RoadsData.data,
      qt_meta_data_RoadsData,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RoadsData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RoadsData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RoadsData.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RoadsData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

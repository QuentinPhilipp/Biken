/****************************************************************************
** Meta object code from reading C++ file 'roadsdata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../routing/roadsdata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'roadsdata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RoadsData_t {
    QByteArrayData data[8];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RoadsData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RoadsData_t qt_meta_stringdata_RoadsData = {
    {
QT_MOC_LITERAL(0, 0, 9), // "RoadsData"
QT_MOC_LITERAL(1, 10, 4), // "test"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 8), // "getFromX"
QT_MOC_LITERAL(4, 25, 1), // "i"
QT_MOC_LITERAL(5, 27, 8), // "getFromY"
QT_MOC_LITERAL(6, 36, 6), // "getToX"
QT_MOC_LITERAL(7, 43, 6) // "getToY"

    },
    "RoadsData\0test\0\0getFromX\0i\0getFromY\0"
    "getToX\0getToY"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RoadsData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x02 /* Public */,
       3,    1,   40,    2, 0x02 /* Public */,
       5,    0,   43,    2, 0x02 /* Public */,
       6,    0,   44,    2, 0x02 /* Public */,
       7,    0,   45,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Double, QMetaType::Int,    4,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,

       0        // eod
};

void RoadsData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RoadsData *_t = static_cast<RoadsData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->test(); break;
        case 1: { double _r = _t->getFromX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 2: { double _r = _t->getFromY();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 3: { double _r = _t->getToX();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 4: { double _r = _t->getToY();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject RoadsData::staticMetaObject = {
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
        return static_cast<void*>(const_cast< RoadsData*>(this));
    return QObject::qt_metacast(_clname);
}

int RoadsData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

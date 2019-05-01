/****************************************************************************
** Meta object code from reading C++ file 'weather.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../routing/weather.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'weather.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Weather_t {
    QByteArrayData data[13];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Weather_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Weather_t qt_meta_stringdata_Weather = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Weather"
QT_MOC_LITERAL(1, 8, 14), // "createForecast"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "lat"
QT_MOC_LITERAL(4, 28, 3), // "lon"
QT_MOC_LITERAL(5, 32, 14), // "changeForecast"
QT_MOC_LITERAL(6, 47, 2), // "id"
QT_MOC_LITERAL(7, 50, 10), // "findActive"
QT_MOC_LITERAL(8, 61, 22), // "getActiveWindDirection"
QT_MOC_LITERAL(9, 84, 18), // "getActiveWindSpeed"
QT_MOC_LITERAL(10, 103, 13), // "getActiveTemp"
QT_MOC_LITERAL(11, 117, 20), // "getActiveDescription"
QT_MOC_LITERAL(12, 138, 13) // "getActiveIcon"

    },
    "Weather\0createForecast\0\0lat\0lon\0"
    "changeForecast\0id\0findActive\0"
    "getActiveWindDirection\0getActiveWindSpeed\0"
    "getActiveTemp\0getActiveDescription\0"
    "getActiveIcon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Weather[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x0a /* Public */,
       5,    1,   59,    2, 0x0a /* Public */,
       7,    0,   62,    2, 0x0a /* Public */,
       8,    0,   63,    2, 0x0a /* Public */,
       9,    0,   64,    2, 0x0a /* Public */,
      10,    0,   65,    2, 0x0a /* Public */,
      11,    0,   66,    2, 0x0a /* Public */,
      12,    0,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Int,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::QString,
    QMetaType::QString,

       0        // eod
};

void Weather::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Weather *_t = static_cast<Weather *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createForecast((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->changeForecast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: { int _r = _t->findActive();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { double _r = _t->getActiveWindDirection();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 4: { double _r = _t->getActiveWindSpeed();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 5: { double _r = _t->getActiveTemp();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 6: { QString _r = _t->getActiveDescription();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 7: { QString _r = _t->getActiveIcon();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Weather::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Weather.data,
      qt_meta_data_Weather,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Weather::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Weather::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Weather.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Weather::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

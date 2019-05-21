/****************************************************************************
** Meta object code from reading C++ file 'card.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../routing/card.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'card.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Card_t {
    QByteArrayData data[9];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Card_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Card_t qt_meta_stringdata_Card = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Card"
QT_MOC_LITERAL(1, 5, 9), // "createMap"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 10), // "RouteNodes"
QT_MOC_LITERAL(4, 27, 12), // "DataManager*"
QT_MOC_LITERAL(5, 40, 2), // "db"
QT_MOC_LITERAL(6, 43, 14), // "getCurrentPath"
QT_MOC_LITERAL(7, 58, 9), // "sendNodes"
QT_MOC_LITERAL(8, 68, 21) // "createGeolocalisedMap"

    },
    "Card\0createMap\0\0RouteNodes\0DataManager*\0"
    "db\0getCurrentPath\0sendNodes\0"
    "createGeolocalisedMap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Card[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x02 /* Public */,
       6,    0,   39,    2, 0x02 /* Public */,
       7,    2,   40,    2, 0x02 /* Public */,
       8,    0,   45,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::QVariantList, 0x80000000 | 4,    3,    5,
    QMetaType::QString,
    QMetaType::QStringList, QMetaType::QVariantList, 0x80000000 | 4,    3,    5,
    QMetaType::Void,

       0        // eod
};

void Card::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Card *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createMap((*reinterpret_cast< QVariantList(*)>(_a[1])),(*reinterpret_cast< DataManager*(*)>(_a[2]))); break;
        case 1: { QString _r = _t->getCurrentPath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 2: { QStringList _r = _t->sendNodes((*reinterpret_cast< QVariantList(*)>(_a[1])),(*reinterpret_cast< DataManager*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->createGeolocalisedMap(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DataManager* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DataManager* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Card::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Card.data,
    qt_meta_data_Card,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Card::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Card::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Card.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Card::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

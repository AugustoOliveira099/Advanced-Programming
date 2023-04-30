/****************************************************************************
** Meta object code from reading C++ file 'modifysaida.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Circuito/modifysaida.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modifysaida.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_modifySaida_t {
    QByteArrayData data[12];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_modifySaida_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_modifySaida_t qt_meta_stringdata_modifySaida = {
    {
QT_MOC_LITERAL(0, 0, 11), // "modifySaida"
QT_MOC_LITERAL(1, 12, 15), // "signModifySaida"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 7), // "idSaida"
QT_MOC_LITERAL(4, 37, 8), // "idOrigem"
QT_MOC_LITERAL(5, 46, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(6, 68, 21), // "on_buttonBox_rejected"
QT_MOC_LITERAL(7, 90, 11), // "slotSaidaID"
QT_MOC_LITERAL(8, 102, 3), // "row"
QT_MOC_LITERAL(9, 106, 18), // "slotIntervaloSaida"
QT_MOC_LITERAL(10, 125, 3), // "min"
QT_MOC_LITERAL(11, 129, 3) // "max"

    },
    "modifySaida\0signModifySaida\0\0idSaida\0"
    "idOrigem\0on_buttonBox_accepted\0"
    "on_buttonBox_rejected\0slotSaidaID\0row\0"
    "slotIntervaloSaida\0min\0max"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_modifySaida[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   44,    2, 0x08 /* Private */,
       6,    0,   45,    2, 0x08 /* Private */,
       7,    1,   46,    2, 0x08 /* Private */,
       9,    2,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,

       0        // eod
};

void modifySaida::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<modifySaida *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signModifySaida((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->on_buttonBox_accepted(); break;
        case 2: _t->on_buttonBox_rejected(); break;
        case 3: _t->slotSaidaID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotIntervaloSaida((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (modifySaida::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&modifySaida::signModifySaida)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject modifySaida::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_modifySaida.data,
    qt_meta_data_modifySaida,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *modifySaida::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *modifySaida::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_modifySaida.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int modifySaida::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void modifySaida::signModifySaida(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

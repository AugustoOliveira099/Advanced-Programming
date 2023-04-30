/****************************************************************************
** Meta object code from reading C++ file 'maincircuito.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Circuito/maincircuito.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maincircuito.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_maincircuito_t {
    QByteArrayData data[28];
    char stringdata0[416];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_maincircuito_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_maincircuito_t qt_meta_stringdata_maincircuito = {
    {
QT_MOC_LITERAL(0, 0, 12), // "maincircuito"
QT_MOC_LITERAL(1, 13, 11), // "signPortaID"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 3), // "row"
QT_MOC_LITERAL(4, 30, 11), // "signSaidaID"
QT_MOC_LITERAL(5, 42, 18), // "signIntervaloPorta"
QT_MOC_LITERAL(6, 61, 3), // "min"
QT_MOC_LITERAL(7, 65, 3), // "max"
QT_MOC_LITERAL(8, 69, 18), // "signIntervaloSaida"
QT_MOC_LITERAL(9, 88, 23), // "on_actionNovo_triggered"
QT_MOC_LITERAL(10, 112, 22), // "on_actionLer_triggered"
QT_MOC_LITERAL(11, 135, 25), // "on_actionSalvar_triggered"
QT_MOC_LITERAL(12, 161, 23), // "on_actionSair_triggered"
QT_MOC_LITERAL(13, 185, 31), // "on_actionGerar_tabela_triggered"
QT_MOC_LITERAL(14, 217, 41), // "on_portasConexoesWidget_cellD..."
QT_MOC_LITERAL(15, 259, 33), // "on_saidasWidget_cellDoubleCli..."
QT_MOC_LITERAL(16, 293, 15), // "slotNewCircuito"
QT_MOC_LITERAL(17, 309, 9), // "nEntradas"
QT_MOC_LITERAL(18, 319, 7), // "nSaidas"
QT_MOC_LITERAL(19, 327, 7), // "nPortas"
QT_MOC_LITERAL(20, 335, 15), // "slotModifyPorta"
QT_MOC_LITERAL(21, 351, 7), // "idPorta"
QT_MOC_LITERAL(22, 359, 9), // "tipoPorta"
QT_MOC_LITERAL(23, 369, 10), // "QString[4]"
QT_MOC_LITERAL(24, 380, 2), // "id"
QT_MOC_LITERAL(25, 383, 15), // "slotModifySaida"
QT_MOC_LITERAL(26, 399, 7), // "idSaida"
QT_MOC_LITERAL(27, 407, 8) // "idOrigem"

    },
    "maincircuito\0signPortaID\0\0row\0signSaidaID\0"
    "signIntervaloPorta\0min\0max\0"
    "signIntervaloSaida\0on_actionNovo_triggered\0"
    "on_actionLer_triggered\0on_actionSalvar_triggered\0"
    "on_actionSair_triggered\0"
    "on_actionGerar_tabela_triggered\0"
    "on_portasConexoesWidget_cellDoubleClicked\0"
    "on_saidasWidget_cellDoubleClicked\0"
    "slotNewCircuito\0nEntradas\0nSaidas\0"
    "nPortas\0slotModifyPorta\0idPorta\0"
    "tipoPorta\0QString[4]\0id\0slotModifySaida\0"
    "idSaida\0idOrigem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_maincircuito[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,
       5,    2,   90,    2, 0x06 /* Public */,
       8,    2,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  100,    2, 0x08 /* Private */,
      10,    0,  101,    2, 0x08 /* Private */,
      11,    0,  102,    2, 0x08 /* Private */,
      12,    0,  103,    2, 0x08 /* Private */,
      13,    0,  104,    2, 0x08 /* Private */,
      14,    2,  105,    2, 0x08 /* Private */,
      15,    2,  110,    2, 0x08 /* Private */,
      16,    3,  115,    2, 0x08 /* Private */,
      20,    4,  122,    2, 0x08 /* Private */,
      25,    2,  131,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   17,   18,   19,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, 0x80000000 | 23,   21,   22,   17,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   26,   27,

       0        // eod
};

void maincircuito::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<maincircuito *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signPortaID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signSaidaID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signIntervaloPorta((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->signIntervaloSaida((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->on_actionNovo_triggered(); break;
        case 5: _t->on_actionLer_triggered(); break;
        case 6: _t->on_actionSalvar_triggered(); break;
        case 7: _t->on_actionSair_triggered(); break;
        case 8: _t->on_actionGerar_tabela_triggered(); break;
        case 9: _t->on_portasConexoesWidget_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->on_saidasWidget_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->slotNewCircuito((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 12: _t->slotModifyPorta((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)[4]>(_a[4]))); break;
        case 13: _t->slotModifySaida((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (maincircuito::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&maincircuito::signPortaID)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (maincircuito::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&maincircuito::signSaidaID)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (maincircuito::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&maincircuito::signIntervaloPorta)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (maincircuito::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&maincircuito::signIntervaloSaida)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject maincircuito::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_maincircuito.data,
    qt_meta_data_maincircuito,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *maincircuito::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *maincircuito::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_maincircuito.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int maincircuito::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void maincircuito::signPortaID(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void maincircuito::signSaidaID(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void maincircuito::signIntervaloPorta(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void maincircuito::signIntervaloSaida(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

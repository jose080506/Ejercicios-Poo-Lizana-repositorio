/****************************************************************************
** Meta object code from reading C++ file 'kanban.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../kanban.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kanban.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN12KanbanWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto KanbanWidget::qt_create_metaobjectdata<qt_meta_tag_ZN12KanbanWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "KanbanWidget",
        "slot_actualizarTablero",
        "",
        "slot_tableroRecibido",
        "datos",
        "slot_operacionCompletada",
        "slot_errorOcurrido",
        "mensaje",
        "slot_nuevaColumna",
        "slot_eliminarColumna",
        "columnaId",
        "slot_nuevaTarjeta",
        "slot_editarTarjeta",
        "tarjetaId",
        "titulo",
        "descripcion",
        "slot_eliminarTarjeta",
        "slot_moverTarjetaIzquierda",
        "columnaActualId",
        "slot_moverTarjetaDerecha",
        "slot_reordenarTarjetas",
        "QList<int>",
        "orden"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'slot_actualizarTablero'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slot_tableroRecibido'
        QtMocHelpers::SlotData<void(const QByteArray &)>(3, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QByteArray, 4 },
        }}),
        // Slot 'slot_operacionCompletada'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slot_errorOcurrido'
        QtMocHelpers::SlotData<void(const QString &)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Slot 'slot_nuevaColumna'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slot_eliminarColumna'
        QtMocHelpers::SlotData<void(int)>(9, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 10 },
        }}),
        // Slot 'slot_nuevaTarjeta'
        QtMocHelpers::SlotData<void(int)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 10 },
        }}),
        // Slot 'slot_editarTarjeta'
        QtMocHelpers::SlotData<void(int, const QString &, const QString &)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 13 }, { QMetaType::QString, 14 }, { QMetaType::QString, 15 },
        }}),
        // Slot 'slot_eliminarTarjeta'
        QtMocHelpers::SlotData<void(int)>(16, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 13 },
        }}),
        // Slot 'slot_moverTarjetaIzquierda'
        QtMocHelpers::SlotData<void(int, int)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 13 }, { QMetaType::Int, 18 },
        }}),
        // Slot 'slot_moverTarjetaDerecha'
        QtMocHelpers::SlotData<void(int, int)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 13 }, { QMetaType::Int, 18 },
        }}),
        // Slot 'slot_reordenarTarjetas'
        QtMocHelpers::SlotData<void(int, QList<int>)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 10 }, { 0x80000000 | 21, 22 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<KanbanWidget, qt_meta_tag_ZN12KanbanWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject KanbanWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12KanbanWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12KanbanWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12KanbanWidgetE_t>.metaTypes,
    nullptr
} };

void KanbanWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<KanbanWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->slot_actualizarTablero(); break;
        case 1: _t->slot_tableroRecibido((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 2: _t->slot_operacionCompletada(); break;
        case 3: _t->slot_errorOcurrido((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->slot_nuevaColumna(); break;
        case 5: _t->slot_eliminarColumna((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->slot_nuevaTarjeta((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->slot_editarTarjeta((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3]))); break;
        case 8: _t->slot_eliminarTarjeta((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->slot_moverTarjetaIzquierda((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 10: _t->slot_moverTarjetaDerecha((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 11: _t->slot_reordenarTarjetas((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QList<int>>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<int> >(); break;
            }
            break;
        }
    }
}

const QMetaObject *KanbanWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KanbanWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12KanbanWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int KanbanWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP

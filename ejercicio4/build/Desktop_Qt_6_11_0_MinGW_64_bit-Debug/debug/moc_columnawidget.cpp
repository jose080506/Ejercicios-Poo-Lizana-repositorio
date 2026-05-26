/****************************************************************************
** Meta object code from reading C++ file 'columnawidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../columnawidget.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'columnawidget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13ColumnaWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto ColumnaWidget::qt_create_metaobjectdata<qt_meta_tag_ZN13ColumnaWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ColumnaWidget",
        "signal_nuevaTarjeta",
        "",
        "columnaId",
        "signal_eliminarColumna",
        "signal_editarTarjeta",
        "tarjetaId",
        "titulo",
        "descripcion",
        "signal_eliminarTarjeta",
        "signal_moverTarjetaIzquierda",
        "signal_moverTarjetaDerecha",
        "signal_reordenar",
        "QList<int>",
        "orden",
        "slot_nuevaTarjeta",
        "slot_eliminarColumna",
        "slot_editarTarjeta",
        "id",
        "slot_eliminarTarjeta",
        "slot_moverIzquierda",
        "slot_moverDerecha",
        "slot_subirTarjeta",
        "slot_bajarTarjeta"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'signal_nuevaTarjeta'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'signal_eliminarColumna'
        QtMocHelpers::SignalData<void(int)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'signal_editarTarjeta'
        QtMocHelpers::SignalData<void(int, const QString &, const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 }, { QMetaType::QString, 7 }, { QMetaType::QString, 8 },
        }}),
        // Signal 'signal_eliminarTarjeta'
        QtMocHelpers::SignalData<void(int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Signal 'signal_moverTarjetaIzquierda'
        QtMocHelpers::SignalData<void(int, int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 }, { QMetaType::Int, 3 },
        }}),
        // Signal 'signal_moverTarjetaDerecha'
        QtMocHelpers::SignalData<void(int, int)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 }, { QMetaType::Int, 3 },
        }}),
        // Signal 'signal_reordenar'
        QtMocHelpers::SignalData<void(int, QList<int>)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { 0x80000000 | 13, 14 },
        }}),
        // Slot 'slot_nuevaTarjeta'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slot_eliminarColumna'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slot_editarTarjeta'
        QtMocHelpers::SlotData<void(int, const QString &, const QString &)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 18 }, { QMetaType::QString, 7 }, { QMetaType::QString, 8 },
        }}),
        // Slot 'slot_eliminarTarjeta'
        QtMocHelpers::SlotData<void(int)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 18 },
        }}),
        // Slot 'slot_moverIzquierda'
        QtMocHelpers::SlotData<void(int)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Slot 'slot_moverDerecha'
        QtMocHelpers::SlotData<void(int)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Slot 'slot_subirTarjeta'
        QtMocHelpers::SlotData<void(int)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Slot 'slot_bajarTarjeta'
        QtMocHelpers::SlotData<void(int)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ColumnaWidget, qt_meta_tag_ZN13ColumnaWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ColumnaWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ColumnaWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ColumnaWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13ColumnaWidgetE_t>.metaTypes,
    nullptr
} };

void ColumnaWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ColumnaWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->signal_nuevaTarjeta((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->signal_eliminarColumna((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->signal_editarTarjeta((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3]))); break;
        case 3: _t->signal_eliminarTarjeta((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->signal_moverTarjetaIzquierda((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->signal_moverTarjetaDerecha((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 6: _t->signal_reordenar((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QList<int>>>(_a[2]))); break;
        case 7: _t->slot_nuevaTarjeta(); break;
        case 8: _t->slot_eliminarColumna(); break;
        case 9: _t->slot_editarTarjeta((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3]))); break;
        case 10: _t->slot_eliminarTarjeta((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->slot_moverIzquierda((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->slot_moverDerecha((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->slot_subirTarjeta((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->slot_bajarTarjeta((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<int> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ColumnaWidget::*)(int )>(_a, &ColumnaWidget::signal_nuevaTarjeta, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ColumnaWidget::*)(int )>(_a, &ColumnaWidget::signal_eliminarColumna, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ColumnaWidget::*)(int , const QString & , const QString & )>(_a, &ColumnaWidget::signal_editarTarjeta, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ColumnaWidget::*)(int )>(_a, &ColumnaWidget::signal_eliminarTarjeta, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ColumnaWidget::*)(int , int )>(_a, &ColumnaWidget::signal_moverTarjetaIzquierda, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ColumnaWidget::*)(int , int )>(_a, &ColumnaWidget::signal_moverTarjetaDerecha, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (ColumnaWidget::*)(int , QList<int> )>(_a, &ColumnaWidget::signal_reordenar, 6))
            return;
    }
}

const QMetaObject *ColumnaWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ColumnaWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ColumnaWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ColumnaWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void ColumnaWidget::signal_nuevaTarjeta(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ColumnaWidget::signal_eliminarColumna(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void ColumnaWidget::signal_editarTarjeta(int _t1, const QString & _t2, const QString & _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3);
}

// SIGNAL 3
void ColumnaWidget::signal_eliminarTarjeta(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void ColumnaWidget::signal_moverTarjetaIzquierda(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void ColumnaWidget::signal_moverTarjetaDerecha(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void ColumnaWidget::signal_reordenar(int _t1, QList<int> _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}
QT_WARNING_POP

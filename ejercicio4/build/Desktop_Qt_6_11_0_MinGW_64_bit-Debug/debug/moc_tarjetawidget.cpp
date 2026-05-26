/****************************************************************************
** Meta object code from reading C++ file 'tarjetawidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../tarjetawidget.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tarjetawidget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13TarjetaWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto TarjetaWidget::qt_create_metaobjectdata<qt_meta_tag_ZN13TarjetaWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TarjetaWidget",
        "signal_editar",
        "",
        "id",
        "titulo",
        "descripcion",
        "signal_eliminar",
        "signal_moverIzquierda",
        "signal_moverDerecha",
        "signal_subir",
        "signal_bajar",
        "slot_editar",
        "slot_eliminar",
        "slot_moverIzquierda",
        "slot_moverDerecha",
        "slot_subir",
        "slot_bajar"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'signal_editar'
        QtMocHelpers::SignalData<void(int, const QString &, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { QMetaType::QString, 4 }, { QMetaType::QString, 5 },
        }}),
        // Signal 'signal_eliminar'
        QtMocHelpers::SignalData<void(int)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'signal_moverIzquierda'
        QtMocHelpers::SignalData<void(int)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'signal_moverDerecha'
        QtMocHelpers::SignalData<void(int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'signal_subir'
        QtMocHelpers::SignalData<void(int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'signal_bajar'
        QtMocHelpers::SignalData<void(int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Slot 'slot_editar'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slot_eliminar'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slot_moverIzquierda'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slot_moverDerecha'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slot_subir'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slot_bajar'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TarjetaWidget, qt_meta_tag_ZN13TarjetaWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TarjetaWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13TarjetaWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13TarjetaWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13TarjetaWidgetE_t>.metaTypes,
    nullptr
} };

void TarjetaWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TarjetaWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->signal_editar((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3]))); break;
        case 1: _t->signal_eliminar((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->signal_moverIzquierda((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->signal_moverDerecha((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->signal_subir((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->signal_bajar((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->slot_editar(); break;
        case 7: _t->slot_eliminar(); break;
        case 8: _t->slot_moverIzquierda(); break;
        case 9: _t->slot_moverDerecha(); break;
        case 10: _t->slot_subir(); break;
        case 11: _t->slot_bajar(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TarjetaWidget::*)(int , const QString & , const QString & )>(_a, &TarjetaWidget::signal_editar, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (TarjetaWidget::*)(int )>(_a, &TarjetaWidget::signal_eliminar, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (TarjetaWidget::*)(int )>(_a, &TarjetaWidget::signal_moverIzquierda, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (TarjetaWidget::*)(int )>(_a, &TarjetaWidget::signal_moverDerecha, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (TarjetaWidget::*)(int )>(_a, &TarjetaWidget::signal_subir, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (TarjetaWidget::*)(int )>(_a, &TarjetaWidget::signal_bajar, 5))
            return;
    }
}

const QMetaObject *TarjetaWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TarjetaWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13TarjetaWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TarjetaWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void TarjetaWidget::signal_editar(int _t1, const QString & _t2, const QString & _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3);
}

// SIGNAL 1
void TarjetaWidget::signal_eliminar(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void TarjetaWidget::signal_moverIzquierda(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void TarjetaWidget::signal_moverDerecha(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void TarjetaWidget::signal_subir(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void TarjetaWidget::signal_bajar(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP

#include "columnawidget.h"
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QFrame>

ColumnaWidget::ColumnaWidget(int id, const QString &nombre, QWidget *parent)
    : QWidget(parent), id(id), nombre(nombre)
{
    setMinimumWidth(240);
    setMaximumWidth(270);
    setStyleSheet(
        "ColumnaWidget {"
        "  background-color: #ebecf0;"
        "  border-radius: 8px;"
        "}"
    );

    // ── Encabezado ────────────────────────────────────────────────────────────
    QLabel *labelNombre = new QLabel(nombre);
    labelNombre->setStyleSheet(
        "font-size: 14px; font-weight: bold; padding: 4px 2px;"
    );

    QPushButton *btnEliminarCol = new QPushButton("✕");
    btnEliminarCol->setFixedSize(24, 24);
    btnEliminarCol->setToolTip("Eliminar columna");
    btnEliminarCol->setStyleSheet(
        "color: #e53935; background: transparent; border: none;"
    );

    QHBoxLayout *headerLayout = new QHBoxLayout;
    headerLayout->addWidget(labelNombre);
    headerLayout->addStretch();
    headerLayout->addWidget(btnEliminarCol);
    headerLayout->setContentsMargins(8, 6, 6, 4);

    // ── Área de tarjetas ──────────────────────────────────────────────────────
    contenedorTarjetas = new QWidget;
    layoutTarjetas = new QVBoxLayout(contenedorTarjetas);
    layoutTarjetas->setAlignment(Qt::AlignTop);
    layoutTarjetas->setSpacing(6);
    layoutTarjetas->setContentsMargins(6, 4, 6, 4);

    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget(contenedorTarjetas);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // ── Botón nueva tarjeta ───────────────────────────────────────────────────
    QPushButton *btnNueva = new QPushButton("+ Agregar tarjeta");
    btnNueva->setStyleSheet(
        "QPushButton {"
        "  background-color: #0079bf; color: white;"
        "  border-radius: 4px; padding: 6px;"
        "  font-size: 12px;"
        "}"
        "QPushButton:hover { background-color: #026aa7; }"
    );

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(headerLayout);
    layout->addWidget(scroll);
    layout->addWidget(btnNueva);
    layout->setContentsMargins(0, 0, 0, 8);
    layout->setSpacing(0);

    connect(btnNueva,       SIGNAL(clicked()), this, SLOT(slot_nuevaTarjeta()));
    connect(btnEliminarCol, SIGNAL(clicked()), this, SLOT(slot_eliminarColumna()));
}

void ColumnaWidget::agregarTarjeta(int tarjetaId, const QString &titulo,
                                   const QString &descripcion) {
    TarjetaWidget *tarjeta = new TarjetaWidget(tarjetaId, titulo, descripcion);
    layoutTarjetas->addWidget(tarjeta);

    connect(tarjeta, SIGNAL(signal_editar(int, QString, QString)),
            this,    SLOT(slot_editarTarjeta(int, QString, QString)));
    connect(tarjeta, SIGNAL(signal_eliminar(int)),
            this,    SLOT(slot_eliminarTarjeta(int)));
    connect(tarjeta, SIGNAL(signal_moverIzquierda(int)),
            this,    SLOT(slot_moverIzquierda(int)));
    connect(tarjeta, SIGNAL(signal_moverDerecha(int)),
            this,    SLOT(slot_moverDerecha(int)));
}

void ColumnaWidget::limpiarTarjetas() {
    QLayoutItem *item;
    while ((item = layoutTarjetas->takeAt(0)) != nullptr) {
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }
}

void ColumnaWidget::slot_nuevaTarjeta()          { emit signal_nuevaTarjeta(id); }
void ColumnaWidget::slot_eliminarColumna()        { emit signal_eliminarColumna(id); }

void ColumnaWidget::slot_editarTarjeta(int tarjetaId, const QString &titulo,
                                        const QString &descripcion) {
    emit signal_editarTarjeta(tarjetaId, titulo, descripcion);
}

void ColumnaWidget::slot_eliminarTarjeta(int tarjetaId) {
    emit signal_eliminarTarjeta(tarjetaId);
}

void ColumnaWidget::slot_moverIzquierda(int tarjetaId) {
    emit signal_moverTarjetaIzquierda(tarjetaId, id);
}

void ColumnaWidget::slot_moverDerecha(int tarjetaId) {
    emit signal_moverTarjetaDerecha(tarjetaId, id);
}

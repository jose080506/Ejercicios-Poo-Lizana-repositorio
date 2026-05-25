#include "tarjetawidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLineEdit>

TarjetaWidget::TarjetaWidget(int id, const QString &titulo,
                              const QString &descripcion, QWidget *parent)
    : QWidget(parent), id(id), titulo(titulo), descripcion(descripcion)
{
    setStyleSheet(
        "TarjetaWidget {"
        "  background-color: #ffffff;"
        "  border: 1px solid #ddd;"
        "  border-radius: 6px;"
        "}"
    );

    QLabel *labelTitulo = new QLabel("<b>" + titulo + "</b>");
    labelTitulo->setWordWrap(true);
    labelTitulo->setStyleSheet("font-size: 13px;");

    QLabel *labelDesc = new QLabel(descripcion);
    labelDesc->setWordWrap(true);
    labelDesc->setStyleSheet("color: #666; font-size: 11px;");
    labelDesc->setVisible(!descripcion.isEmpty());

    QPushButton *btnIzq = new QPushButton("←");
    QPushButton *btnDer = new QPushButton("→");
    btnIzq->setFixedSize(30, 24);
    btnDer->setFixedSize(30, 24);
    btnIzq->setToolTip("Mover a columna anterior");
    btnDer->setToolTip("Mover a columna siguiente");

    QPushButton *btnEditar   = new QPushButton("✏");
    QPushButton *btnEliminar = new QPushButton("✕");
    btnEditar->setFixedSize(30, 24);
    btnEliminar->setFixedSize(30, 24);
    btnEliminar->setStyleSheet("color: #e53935;");

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(btnIzq);
    btnLayout->addWidget(btnDer);
    btnLayout->addStretch();
    btnLayout->addWidget(btnEditar);
    btnLayout->addWidget(btnEliminar);
    btnLayout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(labelTitulo);
    layout->addWidget(labelDesc);
    layout->addLayout(btnLayout);
    layout->setContentsMargins(8, 8, 8, 6);
    layout->setSpacing(4);

    connect(btnEditar,   SIGNAL(clicked()), this, SLOT(slot_editar()));
    connect(btnEliminar, SIGNAL(clicked()), this, SLOT(slot_eliminar()));
    connect(btnIzq,      SIGNAL(clicked()), this, SLOT(slot_moverIzquierda()));
    connect(btnDer,      SIGNAL(clicked()), this, SLOT(slot_moverDerecha()));
}

void TarjetaWidget::slot_editar() {
    bool ok;
    QString nuevoTitulo = QInputDialog::getText(
        this, "Editar tarjeta", "Título:",
        QLineEdit::Normal, titulo, &ok
    );
    if (!ok || nuevoTitulo.trimmed().isEmpty()) return;

    QString nuevaDesc = QInputDialog::getText(
        this, "Editar tarjeta", "Descripción:",
        QLineEdit::Normal, descripcion, &ok
    );
    if (!ok) return;

    emit signal_editar(id, nuevoTitulo.trimmed(), nuevaDesc.trimmed());
}

void TarjetaWidget::slot_eliminar()       { emit signal_eliminar(id); }
void TarjetaWidget::slot_moverIzquierda() { emit signal_moverIzquierda(id); }
void TarjetaWidget::slot_moverDerecha()   { emit signal_moverDerecha(id); }

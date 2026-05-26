#include "tarjetawidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
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

    // Fila 1: mover entre columnas (← →)
    QPushButton *btnIzq = new QPushButton("←");
    QPushButton *btnDer = new QPushButton("→");
    btnIzq->setFixedSize(28, 22);
    btnDer->setFixedSize(28, 22);
    btnIzq->setToolTip("Mover a columna anterior");
    btnDer->setToolTip("Mover a columna siguiente");

    // Fila 2: reordenar dentro de columna (↑ ↓) + editar + eliminar
    QPushButton *btnSubir   = new QPushButton("↑");
    QPushButton *btnBajar   = new QPushButton("↓");
    QPushButton *btnEditar  = new QPushButton("✏");
    QPushButton *btnEliminar = new QPushButton("✕");
    btnSubir->setFixedSize(28, 22);
    btnBajar->setFixedSize(28, 22);
    btnEditar->setFixedSize(28, 22);
    btnEliminar->setFixedSize(28, 22);
    btnSubir->setToolTip("Subir en la columna");
    btnBajar->setToolTip("Bajar en la columna");
    btnEliminar->setStyleSheet("color: #e53935;");

    QHBoxLayout *fila1 = new QHBoxLayout;
    fila1->addWidget(btnIzq);
    fila1->addWidget(btnDer);
    fila1->addStretch();
    fila1->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *fila2 = new QHBoxLayout;
    fila2->addWidget(btnSubir);
    fila2->addWidget(btnBajar);
    fila2->addStretch();
    fila2->addWidget(btnEditar);
    fila2->addWidget(btnEliminar);
    fila2->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(labelTitulo);
    layout->addWidget(labelDesc);
    layout->addLayout(fila1);
    layout->addLayout(fila2);
    layout->setContentsMargins(8, 8, 8, 6);
    layout->setSpacing(3);

    connect(btnEditar,   SIGNAL(clicked()), this, SLOT(slot_editar()));
    connect(btnEliminar, SIGNAL(clicked()), this, SLOT(slot_eliminar()));
    connect(btnIzq,      SIGNAL(clicked()), this, SLOT(slot_moverIzquierda()));
    connect(btnDer,      SIGNAL(clicked()), this, SLOT(slot_moverDerecha()));
    connect(btnSubir,    SIGNAL(clicked()), this, SLOT(slot_subir()));
    connect(btnBajar,    SIGNAL(clicked()), this, SLOT(slot_bajar()));
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
void TarjetaWidget::slot_subir()          { emit signal_subir(id); }
void TarjetaWidget::slot_bajar()          { emit signal_bajar(id); }

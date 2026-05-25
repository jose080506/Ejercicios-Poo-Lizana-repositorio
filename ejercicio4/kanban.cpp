#include "kanban.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QInputDialog>
#include <QMessageBox>
#include <QLineEdit>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFrame>
#include <QDebug>

// ─── Datos reales del VPS ─────────────────────────────────────────────────────
static const QString URL_BASE = "http://173.212.209.61";
static const QString USUARIO  = "admin";
static const QString CLAVE    = "admin123";
// ─────────────────────────────────────────────────────────────────────────────

KanbanWidget::KanbanWidget(QWidget *parent) : QWidget(parent) {
    apiClient = new ApiClient(URL_BASE, USUARIO, CLAVE, this);

    // ── Header ────────────────────────────────────────────────────────────────
    QWidget *header = new QWidget;
    header->setFixedHeight(50);
    header->setStyleSheet("background-color: #0079bf;");

    QHBoxLayout *hHeader = new QHBoxLayout(header);
    hHeader->setContentsMargins(16, 0, 16, 0);

    QLabel *lblTitulo = new QLabel("📋  Tablero Kanban — POO 2026");
    lblTitulo->setStyleSheet("color: white; font-size: 16px; font-weight: bold;");

    QLabel *lblVps = new QLabel("VPS: 173.212.209.61");
    lblVps->setStyleSheet("color: rgba(255,255,255,0.7); font-size: 11px;");

    QPushButton *btnNuevaCol = new QPushButton("+ Nueva columna");
    btnNuevaCol->setStyleSheet(
        "QPushButton { background-color: rgba(255,255,255,0.25); color: white;"
        "  border-radius: 4px; padding: 6px 12px; }"
        "QPushButton:hover { background-color: rgba(255,255,255,0.4); }"
    );

    QPushButton *btnActualizar = new QPushButton("🔄  Actualizar");
    btnActualizar->setStyleSheet(
        "QPushButton { background-color: rgba(255,255,255,0.15); color: white;"
        "  border-radius: 4px; padding: 6px 12px; }"
        "QPushButton:hover { background-color: rgba(255,255,255,0.3); }"
    );

    hHeader->addWidget(lblTitulo);
    hHeader->addWidget(lblVps);
    hHeader->addStretch();
    hHeader->addWidget(btnActualizar);
    hHeader->addWidget(btnNuevaCol);

    // ── Área de columnas con scroll horizontal ────────────────────────────────
    QWidget *areaColumnas = new QWidget;
    areaColumnas->setStyleSheet("background-color: #0079bf;");
    layoutColumnas = new QHBoxLayout(areaColumnas);
    layoutColumnas->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    layoutColumnas->setSpacing(12);
    layoutColumnas->setContentsMargins(12, 12, 12, 12);

    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget(areaColumnas);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // ── Layout principal ──────────────────────────────────────────────────────
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(0, 0, 0, 0);
    layoutPrincipal->setSpacing(0);
    layoutPrincipal->addWidget(header);
    layoutPrincipal->addWidget(scroll);

    // ── Conexiones ────────────────────────────────────────────────────────────
    connect(btnNuevaCol,   SIGNAL(clicked()), this, SLOT(slot_nuevaColumna()));
    connect(btnActualizar, SIGNAL(clicked()), this, SLOT(slot_actualizarTablero()));

    connect(apiClient, SIGNAL(tableroRecibido(QByteArray)),
            this,      SLOT(slot_tableroRecibido(QByteArray)));
    connect(apiClient, SIGNAL(operacionCompletada()),
            this,      SLOT(slot_operacionCompletada()));
    connect(apiClient, SIGNAL(errorOcurrido(QString)),
            this,      SLOT(slot_errorOcurrido(QString)));

    // ── Polling cada 5 segundos ───────────────────────────────────────────────
    timerPolling = new QTimer(this);
    connect(timerPolling, SIGNAL(timeout()), this, SLOT(slot_actualizarTablero()));
    timerPolling->start(5000);

    slot_actualizarTablero();
}

// ── Red ───────────────────────────────────────────────────────────────────────

void KanbanWidget::slot_actualizarTablero() {
    apiClient->obtenerTablero();
}

void KanbanWidget::slot_tableroRecibido(const QByteArray &datos) {
    QJsonDocument doc = QJsonDocument::fromJson(datos);
    if (!doc.isArray()) {
        qDebug() << "[Kanban] Respuesta inesperada:" << datos;
        return;
    }

    limpiarColumnas();
    idsColumnas.clear();

    QJsonArray columnasJson = doc.array();
    for (const QJsonValue &val : columnasJson) {
        QJsonObject colObj = val.toObject();
        int     colId     = colObj["id"].toInt();
        QString colNombre = colObj["nombre"].toString();

        idsColumnas.append(colId);

        ColumnaWidget *col = new ColumnaWidget(colId, colNombre);

        QJsonArray tarjetas = colObj["tarjetas"].toArray();
        for (const QJsonValue &tv : tarjetas) {
            QJsonObject t = tv.toObject();
            col->agregarTarjeta(
                t["id"].toInt(),
                t["titulo"].toString(),
                t["descripcion"].toString()
            );
        }

        conectarColumna(col);
        layoutColumnas->addWidget(col);
        columnas.append(col);
    }
}

void KanbanWidget::slot_operacionCompletada() {
    slot_actualizarTablero();
}

void KanbanWidget::slot_errorOcurrido(const QString &mensaje) {
    qDebug() << "[Kanban] Error:" << mensaje;
    QMessageBox::warning(this, "Error de red",
        "No se pudo conectar al VPS (173.212.209.61).\n\n" + mensaje);
}

// ── Columnas ──────────────────────────────────────────────────────────────────

void KanbanWidget::slot_nuevaColumna() {
    bool ok;
    QString nombre = QInputDialog::getText(
        this, "Nueva columna", "Nombre:", QLineEdit::Normal, "", &ok
    );
    if (ok && !nombre.trimmed().isEmpty())
        apiClient->crearColumna(nombre.trimmed());
}

void KanbanWidget::slot_eliminarColumna(int columnaId) {
    auto resp = QMessageBox::question(
        this, "Eliminar columna",
        "¿Eliminar esta columna y todas sus tarjetas?"
    );
    if (resp == QMessageBox::Yes)
        apiClient->eliminarColumna(columnaId);
}

// ── Tarjetas ──────────────────────────────────────────────────────────────────

void KanbanWidget::slot_nuevaTarjeta(int columnaId) {
    bool ok;
    QString titulo = QInputDialog::getText(
        this, "Nueva tarjeta", "Título:", QLineEdit::Normal, "", &ok
    );
    if (!ok || titulo.trimmed().isEmpty()) return;

    QString desc = QInputDialog::getText(
        this, "Nueva tarjeta", "Descripción (opcional):",
        QLineEdit::Normal, "", &ok
    );
    if (!ok) return;

    apiClient->crearTarjeta(titulo.trimmed(), desc.trimmed(), columnaId);
}

void KanbanWidget::slot_editarTarjeta(int tarjetaId, const QString &titulo,
                                       const QString &descripcion) {
    apiClient->editarTarjeta(tarjetaId, titulo, descripcion);
}

void KanbanWidget::slot_eliminarTarjeta(int tarjetaId) {
    auto resp = QMessageBox::question(this, "Eliminar tarjeta",
                                      "¿Eliminar esta tarjeta?");
    if (resp == QMessageBox::Yes)
        apiClient->eliminarTarjeta(tarjetaId);
}

void KanbanWidget::slot_moverTarjetaIzquierda(int tarjetaId, int columnaActualId) {
    int destino = columnaVecina(columnaActualId, -1);
    if (destino == -1) {
        QMessageBox::information(this, "Info", "Ya está en la primera columna.");
        return;
    }
    apiClient->moverTarjeta(tarjetaId, destino);
}

void KanbanWidget::slot_moverTarjetaDerecha(int tarjetaId, int columnaActualId) {
    int destino = columnaVecina(columnaActualId, +1);
    if (destino == -1) {
        QMessageBox::information(this, "Info", "Ya está en la última columna.");
        return;
    }
    apiClient->moverTarjeta(tarjetaId, destino);
}

// ── Helpers ───────────────────────────────────────────────────────────────────

void KanbanWidget::limpiarColumnas() {
    for (ColumnaWidget *col : columnas) {
        layoutColumnas->removeWidget(col);
        col->deleteLater();
    }
    columnas.clear();
}

void KanbanWidget::conectarColumna(ColumnaWidget *col) {
    connect(col, SIGNAL(signal_nuevaTarjeta(int)),
            this, SLOT(slot_nuevaTarjeta(int)));
    connect(col, SIGNAL(signal_eliminarColumna(int)),
            this, SLOT(slot_eliminarColumna(int)));
    connect(col, SIGNAL(signal_editarTarjeta(int, QString, QString)),
            this, SLOT(slot_editarTarjeta(int, QString, QString)));
    connect(col, SIGNAL(signal_eliminarTarjeta(int)),
            this, SLOT(slot_eliminarTarjeta(int)));
    connect(col, SIGNAL(signal_moverTarjetaIzquierda(int, int)),
            this, SLOT(slot_moverTarjetaIzquierda(int, int)));
    connect(col, SIGNAL(signal_moverTarjetaDerecha(int, int)),
            this, SLOT(slot_moverTarjetaDerecha(int, int)));
}

int KanbanWidget::columnaVecina(int columnaActualId, int delta) {
    int idx = idsColumnas.indexOf(columnaActualId);
    if (idx == -1) return -1;
    int nuevo = idx + delta;
    if (nuevo < 0 || nuevo >= idsColumnas.size()) return -1;
    return idsColumnas[nuevo];
}

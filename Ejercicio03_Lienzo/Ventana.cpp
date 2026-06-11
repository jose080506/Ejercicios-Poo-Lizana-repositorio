#include "Ventana.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

// URL del VPS del equipo — reemplazar con la real
namespace {
    const QString URL_VPS = "http://173.212.209.61:8000";
}

// ─── Constructor ──────────────────────────────────────────────────────────────

Ventana::Ventana(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Ejercicio 03 — Lienzo Colaborativo");
    resize(900, 620);

    // crear las tres capas: modelo, vista, sincronizador
    m_modelo = new ModeloDibujo(this);
    m_lienzo = new Lienzo(m_modelo, this);
    m_sinc   = new Sincronizador(URL_VPS, this);

    // toolbar
    armarToolbar();

    // label de estado debajo del lienzo
    m_lblEstado = new QLabel("Teclas 1-9: color  |  Rueda: grosor  |  Click derecho: goma", this);
    m_lblEstado->setStyleSheet("color:#94a3b8; background:#0f0f1a; padding:4px 10px; font-size:11px;");

    // layout central
    QWidget     *central = new QWidget(this);
    QVBoxLayout *lay     = new QVBoxLayout(central);
    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(0);
    lay->addWidget(m_lienzo, 1);
    lay->addWidget(m_lblEstado);
    setCentralWidget(central);

    // conectar señales del sincronizador
    connect(m_sinc, SIGNAL(guardadoOk()),
            this,   SLOT(slot_alGuardarOk()));
    connect(m_sinc, SIGNAL(guardadoError(QString)),
            this,   SLOT(slot_alGuardarError(QString)));
    connect(m_sinc, SIGNAL(dibujoRecuperado(QJsonArray)),
            this,   SLOT(slot_alRecuperar(QJsonArray)));
    connect(m_sinc, SIGNAL(recuperacionError(QString)),
            this,   SLOT(slot_alRecuperarError(QString)));

    // al arrancar: recuperar el dibujo del VPS
    mostrarEstado("Conectando al VPS...", "#60a5fa");
    m_sinc->recuperar();
}

// ─── Toolbar estilo Metro de Windows ─────────────────────────────────────────

void Ventana::armarToolbar()
{
    QToolBar *bar = addToolBar("Principal");
    bar->setMovable(false);
    bar->setStyleSheet(
        "QToolBar { background: #16213e; border-bottom: 1px solid #0f3460; padding: 4px 8px; }"
    );

    // estilo Metro: fondo sólido, sin bordes redondeados, tipografía limpia
    const QString estiloMetro =
        "QPushButton {"
        "  background: #0f3460;"
        "  color: #e2e8f0;"
        "  font-family: 'Segoe UI', sans-serif;"
        "  font-size: 12px;"
        "  font-weight: bold;"
        "  padding: 6px 18px;"
        "  border: none;"
        "  border-radius: 0px;"          // Metro: sin bordes redondeados
        "  min-width: 80px;"
        "}"
        "QPushButton:hover  { background: #1a5276; }"
        "QPushButton:pressed{ background: #0a2540; }";

    // botón Guardar
    QPushButton *btnGuardar = new QPushButton("  Guardar  ");
    btnGuardar->setStyleSheet(estiloMetro);
    bar->addWidget(btnGuardar);
    connect(btnGuardar, SIGNAL(clicked()), this, SLOT(slot_guardar()));

    // separador visual
    bar->addSeparator();

    // botón Limpiar
    QPushButton *btnLimpiar = new QPushButton("  Limpiar  ");
    btnLimpiar->setStyleSheet(estiloMetro);
    bar->addWidget(btnLimpiar);
    connect(btnLimpiar, &QPushButton::clicked, this, [this]() {
        m_modelo->limpiar();
        mostrarEstado("Lienzo limpiado");
    });

    // espacio flexible para empujar el título a la derecha
    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    bar->addWidget(spacer);

    // título
    QLabel *titulo = new QLabel("Lienzo Colaborativo");
    titulo->setStyleSheet("color:#94a3b8; font-family:'Segoe UI'; font-size:13px; padding-right:10px;");
    bar->addWidget(titulo);
}

// ─── Slots ────────────────────────────────────────────────────────────────────

void Ventana::slot_guardar()
{
    mostrarEstado("Guardando...", "#facc15");
    m_sinc->guardar(m_modelo->toJson());
}

void Ventana::slot_alGuardarOk()
{
    mostrarEstado("Guardado correctamente en el VPS", "#4ade80");
}

void Ventana::slot_alGuardarError(const QString &detalle)
{
    mostrarEstado("Error al guardar: " + detalle, "#f87171");
}

void Ventana::slot_alRecuperar(const QJsonArray &trazos)
{
    const int nuevos = m_modelo->mergear(trazos);
    if (nuevos > 0)
        mostrarEstado(QString("Recuperados %1 trazo(s) del VPS").arg(nuevos), "#4ade80");
    else
        mostrarEstado("Lienzo sincronizado — sin cambios nuevos", "#94a3b8");
}

void Ventana::slot_alRecuperarError(const QString &detalle)
{
    mostrarEstado("No se pudo conectar al VPS: " + detalle, "#f87171");
}

// ─── Helper ───────────────────────────────────────────────────────────────────

void Ventana::mostrarEstado(const QString &texto, const QString &color)
{
    m_lblEstado->setText(texto);
    m_lblEstado->setStyleSheet(
        QString("color:%1; background:#0f0f1a; padding:4px 10px; font-size:11px;").arg(color)
    );
}

#include "Lienzo.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QWheelEvent>

// ─── Constructor ──────────────────────────────────────────────────────────────

Lienzo::Lienzo(ModeloDibujo *modelo, QWidget *parent)
    : QWidget(parent)
    , m_modelo(modelo)
    , m_colorActual(interpolarColor(1))   // color inicial: paso 1
{
    setFocusPolicy(Qt::StrongFocus);      // necesario para capturar teclado
    setMouseTracking(false);              // solo eventos con botón presionado
    setAttribute(Qt::WA_OpaquePaintEvent);
    setMinimumSize(600, 400);

    // cuando el modelo cambia, redibujar
    connect(m_modelo, SIGNAL(dibujoModificado()), this, SLOT(update()));
}

// ─── paintEvent: la VISTA renderiza el modelo ─────────────────────────────────

void Lienzo::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // fondo
    p.fillRect(rect(), QColor("#1a1a2e"));

    // dibujar cada trazo con sus puntos interpolados
    for (const Trazo &t : m_modelo->trazos()) {
        if (t.puntos.size() < 2) {
            // punto suelto: un círculo pequeño
            QPen pen(t.esGoma ? QColor("#1a1a2e") : t.color, t.grosor,
                     Qt::SolidLine, Qt::RoundCap);
            p.setPen(pen);
            p.drawPoint(t.puntos.first());
            continue;
        }

        QPen pen(t.esGoma ? QColor("#1a1a2e") : t.color, t.grosor,
                 Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        p.setPen(pen);

        // trazar la curva suavizada con QPainterPath (curva de Bezier)
        QPainterPath path;
        path.moveTo(t.puntos.first());

        for (int i = 1; i < t.puntos.size() - 1; ++i) {
            // punto de control: promedio entre el actual y el siguiente
            QPointF ctrl = (t.puntos[i] + t.puntos[i + 1]) / 2.0;
            path.quadTo(t.puntos[i], ctrl);
        }
        path.lineTo(t.puntos.last());
        p.drawPath(path);
    }

    // mostrar grosor y color actuales en esquina
    p.setPen(Qt::white);
    p.setFont(QFont("Segoe UI", 9));
    p.drawText(8, height() - 8,
               QString("Grosor: %1  Color: %2")
                   .arg(m_grosor)
                   .arg(m_colorActual.name().toUpper()));
}

// ─── Mouse ────────────────────────────────────────────────────────────────────

void Lienzo::mousePressEvent(QMouseEvent *event)
{
    m_dibujando  = (event->button() == Qt::LeftButton);
    m_borrando   = (event->button() == Qt::RightButton);

    if (m_dibujando || m_borrando) {
        m_ultimoPunto = event->pos();
        m_modelo->iniciarTrazo(m_ultimoPunto, m_colorActual,
                               m_grosor, m_borrando);
        // goma más gruesa para borrar con comodidad
        if (m_borrando) m_modelo->trazos();
    }
}

void Lienzo::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_dibujando && !m_borrando) return;

    const QPoint actual = event->pos();

    // interpolación: agregar puntos intermedios para trazo suave
    // e independiente de la velocidad del mouse
    const QList<QPoint> intermedios = interpolar(m_ultimoPunto, actual, 6);
    for (const QPoint &pt : intermedios)
        m_modelo->agregarPunto(pt);

    m_modelo->agregarPunto(actual);
    m_ultimoPunto = actual;
}

void Lienzo::mouseReleaseEvent(QMouseEvent *)
{
    m_modelo->finalizarTrazo();
    m_dibujando = false;
    m_borrando  = false;
}

// ─── Rueda del mouse: controla grosor ────────────────────────────────────────

void Lienzo::wheelEvent(QWheelEvent *event)
{
    // un "tick" de la rueda: ±1 grosor
    const int delta = (event->angleDelta().y() > 0) ? 1 : -1;
    m_grosor = qBound(1, m_grosor + delta, 40);
    update();  // refrescar el indicador de esquina
}

// ─── Teclado: teclas 1-9 cambian el color ────────────────────────────────────

void Lienzo::keyPressEvent(QKeyEvent *event)
{
    const int paso = event->key() - Qt::Key_0;  // '1' -> 1, '2' -> 2, etc.
    if (paso >= 1 && paso <= 9) {
        m_colorActual = interpolarColor(paso);
        update();
    }
}

// ─── Helpers estáticos ───────────────────────────────────────────────────────

// Interpolación de color entre (192,19,76) y (24,233,199) en 9 pasos
QColor Lienzo::interpolarColor(int paso)
{
    // paso va de 1 a 9; t va de 0.0 a 1.0
    const double t = (paso - 1) / 8.0;

    const int r = static_cast<int>(192 + t * (24  - 192));
    const int g = static_cast<int>(19  + t * (233 - 19));
    const int b = static_cast<int>(76  + t * (199 - 76));

    return QColor(r, g, b);
}

// Interpolación de puntos: genera 'pasos' puntos entre desde y hasta
// para que el trazo sea continuo sin importar la velocidad del mouse
QList<QPoint> Lienzo::interpolar(const QPoint &desde, const QPoint &hasta,
                                  int pasos)
{
    QList<QPoint> pts;
    for (int i = 1; i < pasos; ++i) {
        const double t = static_cast<double>(i) / pasos;
        pts << QPoint(
            static_cast<int>(desde.x() + t * (hasta.x() - desde.x())),
            static_cast<int>(desde.y() + t * (hasta.y() - desde.y()))
        );
    }
    return pts;
}

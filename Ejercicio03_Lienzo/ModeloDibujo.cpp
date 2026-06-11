#include "ModeloDibujo.h"

#include <QJsonDocument>

ModeloDibujo::ModeloDibujo(QObject *parent)
    : QObject(parent)
{}

// ─── Gestión de trazos ────────────────────────────────────────────────────────

void ModeloDibujo::iniciarTrazo(const QPoint &punto, const QColor &color,
                                int grosor, bool esGoma)
{
    Trazo t;
    t.puntos << punto;
    t.color  = color;
    t.grosor = grosor;
    t.esGoma = esGoma;
    m_trazos.append(t);
    m_trazando = true;
    emit dibujoModificado();
}

void ModeloDibujo::agregarPunto(const QPoint &punto)
{
    if (!m_trazando || m_trazos.isEmpty()) return;
    m_trazos.last().puntos << punto;
    emit dibujoModificado();
}

void ModeloDibujo::finalizarTrazo()
{
    m_trazando = false;
}

void ModeloDibujo::limpiar()
{
    m_trazos.clear();
    m_trazando = false;
    emit dibujoModificado();
}

// ─── Serialización ────────────────────────────────────────────────────────────

QJsonArray ModeloDibujo::toJson() const
{
    QJsonArray arr;
    for (const Trazo &t : m_trazos) {
        QJsonObject obj;
        QJsonArray  pts;
        for (const QPoint &p : t.puntos) {
            QJsonObject pt;
            pt["x"] = p.x();
            pt["y"] = p.y();
            pts.append(pt);
        }
        obj["puntos"] = pts;
        obj["r"]      = t.color.red();
        obj["g"]      = t.color.green();
        obj["b"]      = t.color.blue();
        obj["grosor"] = t.grosor;
        obj["goma"]   = t.esGoma;
        arr.append(obj);
    }
    return arr;
}

void ModeloDibujo::fromJson(const QJsonArray &arr)
{
    m_trazos.clear();
    for (const QJsonValue &v : arr) {
        QJsonObject obj = v.toObject();
        Trazo t;
        t.color  = QColor(obj["r"].toInt(), obj["g"].toInt(), obj["b"].toInt());
        t.grosor = obj["grosor"].toInt(4);
        t.esGoma = obj["goma"].toBool(false);
        for (const QJsonValue &pv : obj["puntos"].toArray()) {
            QJsonObject pt = pv.toObject();
            t.puntos << QPoint(pt["x"].toInt(), pt["y"].toInt());
        }
        m_trazos.append(t);
    }
    emit dibujoModificado();
}

// ─── Merge colaborativo ───────────────────────────────────────────────────────
// Agrega solo los trazos del servidor que superen la cantidad local:
// preserva lo que el usuario está dibujando y suma lo nuevo.
int ModeloDibujo::mergear(const QJsonArray &trazosServidor)
{
    // cantidad de trazos que ya teníamos localmente
    const int previos = m_trazos.size();

    // trazos del servidor que no tenemos aún (sólo los nuevos)
    for (int i = previos; i < trazosServidor.size(); ++i) {
        QJsonObject obj = trazosServidor[i].toObject();
        Trazo t;
        t.color  = QColor(obj["r"].toInt(), obj["g"].toInt(), obj["b"].toInt());
        t.grosor = obj["grosor"].toInt(4);
        t.esGoma = obj["goma"].toBool(false);
        for (const QJsonValue &pv : obj["puntos"].toArray()) {
            QJsonObject pt = pv.toObject();
            t.puntos << QPoint(pt["x"].toInt(), pt["y"].toInt());
        }
        m_trazos.insert(previos, t);  // insertar antes de los locales
    }

    const int nuevos = trazosServidor.size() - previos;
    if (nuevos > 0) emit dibujoModificado();
    return nuevos;
}

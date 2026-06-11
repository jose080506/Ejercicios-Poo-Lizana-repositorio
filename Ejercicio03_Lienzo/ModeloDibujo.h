#ifndef MODELODIBUJO_H
#define MODELODIBUJO_H

#include <QColor>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QPoint>

// Un trazo: lista de puntos + color + grosor + es goma?
struct Trazo {
    QList<QPoint> puntos;
    QColor color;
    int grosor    = 4;
    bool esGoma   = false;
    QString autor = "yo";  // para el merge colaborativo
};

// Modelo: guarda todos los trazos y los serializa a JSON
class ModeloDibujo : public QObject {
    Q_OBJECT

public:
    explicit ModeloDibujo(QObject *parent = nullptr);

    // Gestión de trazos
    void iniciarTrazo(const QPoint &punto, const QColor &color,
                      int grosor, bool esGoma);
    void agregarPunto(const QPoint &punto);
    void finalizarTrazo();
    void limpiar();

    const QList<Trazo> &trazos() const { return m_trazos; }
    bool hayTrazoActivo() const        { return m_trazando; }

    // Serialización
    QJsonArray toJson()            const;
    void       fromJson(const QJsonArray &arr);

    // Merge colaborativo: agrega solo trazos nuevos del servidor
    int mergear(const QJsonArray &trazosServidor);

signals:
    void dibujoModificado();

private:
    QList<Trazo> m_trazos;
    bool         m_trazando = false;
};

#endif // MODELODIBUJO_H

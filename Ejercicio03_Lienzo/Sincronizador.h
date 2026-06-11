#ifndef SINCRONIZADOR_H
#define SINCRONIZADOR_H

#include <QNetworkAccessManager>
#include <QObject>
#include <QJsonArray>
#include <QString>

// Clase de sincronización con el VPS.
// Responsabilidad única: hablar con la API y emitir señales con el resultado.
class Sincronizador : public QObject {
    Q_OBJECT

public:
    explicit Sincronizador(const QString &baseUrl, QObject *parent = nullptr);

    // Sube el dibujo completo al servidor
    void guardar(const QJsonArray &trazos);

    // Baja el dibujo actual del servidor
    void recuperar();

signals:
    void guardadoOk();
    void guardadoError(const QString &detalle);
    void dibujoRecuperado(const QJsonArray &trazos);
    void recuperacionError(const QString &detalle);

private:
    QNetworkRequest crearRequest(const QString &endpoint) const;

    QNetworkAccessManager m_manager;
    QString               m_baseUrl;
};

#endif // SINCRONIZADOR_H

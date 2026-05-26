#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>
#include <QString>
#include <QList>

class ApiClient : public QObject {
    Q_OBJECT

public:
    explicit ApiClient(const QString &baseUrl,
                       const QString &usuario,
                       const QString &clave,
                       QObject *parent = nullptr);

    // Columnas
    void obtenerTablero();
    void crearColumna(const QString &nombre);
    void eliminarColumna(int id);

    // Tarjetas
    void crearTarjeta(const QString &titulo, const QString &descripcion, int columnaId);
    void editarTarjeta(int id, const QString &titulo, const QString &descripcion);
    void eliminarTarjeta(int id);
    void moverTarjeta(int tarjetaId, int columnaDestinoId);
    void reordenarTarjetas(int columnaId, const QList<int> &orden);

signals:
    void tableroRecibido(const QByteArray &datos);
    void operacionCompletada();
    void errorOcurrido(const QString &mensaje);

private slots:
    void slot_tableroRecibido(QNetworkReply *reply);
    void slot_operacionCompletada(QNetworkReply *reply);

private:
    QNetworkAccessManager *managerGet;
    QNetworkAccessManager *managerMut;
    QString    baseUrl;
    QByteArray credenciales;

    QNetworkRequest crearRequest(const QString &path);
    QNetworkRequest crearRequestJson(const QString &path);
};

#endif // APICLIENT_H

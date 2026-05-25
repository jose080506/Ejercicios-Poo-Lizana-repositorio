#include "apiclient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

ApiClient::ApiClient(const QString &baseUrl, const QString &usuario,
                     const QString &clave, QObject *parent)
    : QObject(parent), baseUrl(baseUrl)
{
    credenciales = (usuario + ":" + clave).toUtf8().toBase64();

    managerGet = new QNetworkAccessManager(this);
    connect(managerGet, SIGNAL(finished(QNetworkReply*)),
            this,       SLOT(slot_tableroRecibido(QNetworkReply*)));

    managerMut = new QNetworkAccessManager(this);
    connect(managerMut, SIGNAL(finished(QNetworkReply*)),
            this,       SLOT(slot_operacionCompletada(QNetworkReply*)));
}

QNetworkRequest ApiClient::crearRequest(const QString &path) {
    QNetworkRequest request;
    request.setUrl(QUrl(baseUrl + path));
    request.setRawHeader("Authorization", "Basic " + credenciales);
    return request;
}

QNetworkRequest ApiClient::crearRequestJson(const QString &path) {
    QNetworkRequest request = crearRequest(path);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    return request;
}

// ── Columnas ──────────────────────────────────────────────────────────────────

void ApiClient::obtenerTablero() {
    managerGet->get(crearRequest("/kanban/columnas"));
}

void ApiClient::crearColumna(const QString &nombre) {
    QJsonObject obj;
    obj["nombre"] = nombre;
    managerMut->post(crearRequestJson("/kanban/columnas"),
                     QJsonDocument(obj).toJson());
}

void ApiClient::eliminarColumna(int id) {
    managerMut->deleteResource(
        crearRequest(QString("/kanban/columnas/%1").arg(id)));
}

// ── Tarjetas ──────────────────────────────────────────────────────────────────

void ApiClient::crearTarjeta(const QString &titulo,
                              const QString &descripcion, int columnaId) {
    QJsonObject obj;
    obj["titulo"]      = titulo;
    obj["descripcion"] = descripcion;
    obj["columna_id"]  = columnaId;
    managerMut->post(crearRequestJson("/kanban/tarjetas"),
                     QJsonDocument(obj).toJson());
}

void ApiClient::editarTarjeta(int id, const QString &titulo,
                               const QString &descripcion) {
    QJsonObject obj;
    obj["titulo"]      = titulo;
    obj["descripcion"] = descripcion;
    managerMut->put(crearRequestJson(QString("/kanban/tarjetas/%1").arg(id)),
                    QJsonDocument(obj).toJson());
}

void ApiClient::eliminarTarjeta(int id) {
    managerMut->deleteResource(
        crearRequest(QString("/kanban/tarjetas/%1").arg(id)));
}

void ApiClient::moverTarjeta(int tarjetaId, int columnaDestinoId) {
    QJsonObject obj;
    obj["columna_destino_id"] = columnaDestinoId;
    managerMut->put(
        crearRequestJson(QString("/kanban/tarjetas/%1/mover").arg(tarjetaId)),
        QJsonDocument(obj).toJson());
}

// ── Slots ─────────────────────────────────────────────────────────────────────

void ApiClient::slot_tableroRecibido(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError)
        emit tableroRecibido(reply->readAll());
    else
        emit errorOcurrido(reply->errorString());
    reply->deleteLater();
}

void ApiClient::slot_operacionCompletada(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError)
        emit operacionCompletada();
    else
        emit errorOcurrido(reply->errorString());
    reply->deleteLater();
}

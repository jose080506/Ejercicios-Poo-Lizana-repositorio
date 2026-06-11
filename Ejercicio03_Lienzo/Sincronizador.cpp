#include "Sincronizador.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

// ─── Constructor ──────────────────────────────────────────────────────────────

Sincronizador::Sincronizador(const QString &baseUrl, QObject *parent)
    : QObject(parent)
    , m_baseUrl(baseUrl)
{}

// ─── Guardar dibujo en el VPS ────────────────────────────────────────────────

void Sincronizador::guardar(const QJsonArray &trazos)
{
    QJsonObject body;
    body["trazos"] = trazos;

    QNetworkReply *reply = m_manager.post(
        crearRequest("/dibujo"),
        QJsonDocument(body).toJson(QJsonDocument::Compact)
    );

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            emit guardadoOk();
        } else {
            emit guardadoError(reply->errorString());
        }
        reply->deleteLater();   // siempre deleteLater, nunca delete directo
    });
}

// ─── Recuperar dibujo del VPS ────────────────────────────────────────────────

void Sincronizador::recuperar()
{
    QNetworkReply *reply = m_manager.get(crearRequest("/dibujo"));

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            emit recuperacionError(reply->errorString());
            reply->deleteLater();
            return;
        }

        const QByteArray cuerpo = reply->readAll();
        reply->deleteLater();

        QJsonParseError err;
        const QJsonDocument doc = QJsonDocument::fromJson(cuerpo, &err);
        if (err.error != QJsonParseError::NoError) {
            emit recuperacionError("JSON inválido: " + err.errorString());
            return;
        }

        const QJsonArray trazos = doc.object().value("trazos").toArray();
        emit dibujoRecuperado(trazos);
    });
}

// ─── Helper: armar el request con headers ────────────────────────────────────

QNetworkRequest Sincronizador::crearRequest(const QString &endpoint) const
{
    QNetworkRequest req{QUrl(m_baseUrl + endpoint)};
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    return req;
}

#ifndef CLIMA_H
#define CLIMA_H

#include <QObject>
#include <QString>

class QNetworkAccessManager;
class QNetworkReply;

// Clase derivada adicional para manejo de datos.
// Hereda de QObject para poder usar signals y slots.
// Encapsula el QNetworkAccessManager y la lógica de consumo de la API.

class Clima : public QObject  {
    Q_OBJECT

public:
    Clima( const QString & apiKey, const QString & ciudad, QObject * parent = nullptr );

    void consultarClima();

signals:
    void climaListo( const QString & info );      // info ya formateado
    void errorClima( const QString & motivo );

private slots:
    void slot_respuesta( QNetworkReply * reply );

private:
    QNetworkAccessManager * manager;
    QString apiKey;
    QString ciudad;
};

#endif // CLIMA_H

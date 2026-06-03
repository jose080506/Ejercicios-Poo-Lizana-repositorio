#include "clima.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

// API usada: OpenWeatherMap (free tier)
// https://api.openweathermap.org/data/2.5/weather?q=Cordoba,AR&appid=KEY&units=metric&lang=es

Clima::Clima( const QString & apiKey, const QString & ciudad, QObject * parent )
    : QObject( parent ),
      apiKey( apiKey ),
      ciudad( ciudad )  {

    manager = new QNetworkAccessManager( this );

    connect( manager, SIGNAL( finished( QNetworkReply * ) ),
             this, SLOT( slot_respuesta( QNetworkReply * ) ) );
}

void Clima::consultarClima()  {
    if ( apiKey.isEmpty() )  {
        emit errorClima( "API key no configurada en config.ini" );
        return;
    }

    QUrl url( "https://api.openweathermap.org/data/2.5/weather" );
    QUrlQuery query;
    query.addQueryItem( "q",     ciudad );
    query.addQueryItem( "appid", apiKey );
    query.addQueryItem( "units", "metric" );
    query.addQueryItem( "lang",  "es" );
    url.setQuery( query );

    QNetworkRequest request( url );
    request.setRawHeader( "User-Agent", "LoginClima 1.0" );

    manager->get( request );
}

void Clima::slot_respuesta( QNetworkReply * reply )  {
    if ( reply->error() != QNetworkReply::NoError )  {
        emit errorClima( reply->errorString() );
        reply->deleteLater();
        return;
    }

    QByteArray datos = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson( datos );
    if ( ! doc.isObject() )  {
        emit errorClima( "Respuesta inválida del servidor" );
        return;
    }

    QJsonObject raiz = doc.object();
    QJsonObject main = raiz.value( "main" ).toObject();
    QJsonObject weather0;
    if ( raiz.value( "weather" ).isArray() &&
         raiz.value( "weather" ).toArray().size() > 0 )  {
        weather0 = raiz.value( "weather" ).toArray().at( 0 ).toObject();
    }

    double temp = main.value( "temp" ).toDouble();
    QString desc = weather0.value( "description" ).toString();

    QString info = QString( "Córdoba: %1 °C, %2" )
                       .arg( QString::number( temp, 'f', 1 ) )
                       .arg( desc );

    emit climaListo( info );
}

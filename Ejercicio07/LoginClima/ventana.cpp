#include "ventana.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QFile>
#include <QDir>
#include <QResizeEvent>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSettings>

static const QString URL_FONDO_DEFAULT =
    "https://images.unsplash.com/photo-1506905925346-21bda4d32df4?w=1920";
static const QString CACHE_FONDO = "fondo_cache.jpg";

Ventana::Ventana( QWidget * parent )
    : Pantalla( parent ),
      pixmapFondo( nullptr )  {

    armarUI();

    manager = new QNetworkAccessManager( this );
    connect( manager, SIGNAL( finished( QNetworkReply * ) ),
             this, SLOT( slot_imagenDescargada( QNetworkReply * ) ) );
}

Ventana::~Ventana()  {
    delete pixmapFondo;
}

void Ventana::armarUI()  {
    setWindowTitle( "Bienvenido" );

    // Fondo: QLabel ocupando todo, debajo de los demás widgets
    lFondo = new QLabel( this );
    lFondo->setScaledContents( false );
    lFondo->setAlignment( Qt::AlignCenter );
    lFondo->setStyleSheet( "background-color: #1c1c1c;" );

    // Tarjeta tipo LinkedIn arriba a la izquierda
    QWidget * tarjeta = new QWidget( this );
    tarjeta->setStyleSheet(
        "background-color: rgba(255, 255, 255, 230); "
        "border-radius: 12px; "
        "padding: 20px;"
    );

    lFoto = new QLabel( tarjeta );
    lFoto->setFixedSize( 120, 120 );
    lFoto->setStyleSheet(
        "background-color: #ccc; border-radius: 60px;"
    );
    lFoto->setAlignment( Qt::AlignCenter );
    lFoto->setText( "Foto" );

    lDescripcion = new QLabel( tarjeta );
    lDescripcion->setWordWrap( true );
    lDescripcion->setText(
        "<h2 style='margin:0;'>José Lizana</h2>"
        "<p style='color:#555; margin:4px 0;'>"
        "Estudiante de Ingeniería en Informática</p>"
        "<p style='margin:8px 0;'>"
        "Desarrollador "
    );
    lDescripcion->setStyleSheet( "color: #222;" );

    QHBoxLayout * lh = new QHBoxLayout;
    lh->addWidget( lFoto );
    lh->addWidget( lDescripcion, 1 );
    tarjeta->setLayout( lh );

    QVBoxLayout * lv = new QVBoxLayout;
    lv->addWidget( tarjeta );
    lv->addStretch( 1 );
    setLayout( lv );

    lFondo->lower();   // mandar el fondo al fondo del z-order
}

void Ventana::mostrar()  {
    // Intentamos primero el cache local; si no existe, descargamos.
    QFile cache( CACHE_FONDO );
    if ( cache.exists() )  {
        pixmapFondo = new QPixmap( CACHE_FONDO );
        aplicarFondo();
        showFullScreen();
        registrarEvento( "Ventana: mostrada con fondo desde cache" );
        return;
    }

    // No hay cache => descargar y esperar a que termine
    QSettings config( "config.ini", QSettings::IniFormat );
    QString url = config.value( "fondo/url", URL_FONDO_DEFAULT ).toString();

    QUrl qurl( url );
    QNetworkRequest request( qurl );
    request.setRawHeader( "User-Agent", "LoginClima 1.0" );
    manager->get( request );

    registrarEvento( "Ventana: descargando fondo desde " + url );
    // OJO: NO se llama show() acá. Se llama recién cuando la imagen llegó.
}

void Ventana::cerrar()  {
    this->close();
    registrarEvento( "Ventana: cerrada" );
}

void Ventana::slot_imagenDescargada( QNetworkReply * reply )  {
    if ( reply->error() != QNetworkReply::NoError )  {
        registrarEvento( "Ventana: error al descargar fondo -> " + reply->errorString() );
        // Mostramos igual con fondo de color sólido (modo offline)
        showFullScreen();
        reply->deleteLater();
        return;
    }

    QByteArray datos = reply->readAll();
    reply->deleteLater();

    // Guardar en cache local
    QFile cache( CACHE_FONDO );
    if ( cache.open( QIODevice::WriteOnly ) )  {
        cache.write( datos );
        cache.close();
    }

    pixmapFondo = new QPixmap;
    pixmapFondo->loadFromData( datos );
    aplicarFondo();

    showFullScreen();
    registrarEvento( "Ventana: mostrada con fondo descargado" );
}

void Ventana::aplicarFondo()  {
    if ( ! pixmapFondo || pixmapFondo->isNull() )  return;

    lFondo->setGeometry( 0, 0, width(), height() );
    QPixmap escalado = pixmapFondo->scaled(
        size(),
        Qt::KeepAspectRatioByExpanding,   // cubre toda la ventana, sin deformar
        Qt::SmoothTransformation
    );
    lFondo->setPixmap( escalado );
}

void Ventana::resizeEvent( QResizeEvent * event )  {
    Pantalla::resizeEvent( event );
    aplicarFondo();
}

#include "modobloqueado.h"

#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QSettings>

ModoBloqueado::ModoBloqueado( QWidget * parent )
    : Pantalla( parent ),
      duracionBloqueo( 15 )  {

    inicializarUI();
    cargarDatos();
    conectarEventos();
    registrarEvento( "Pantalla de bloqueo inicializada" );
}

ModoBloqueado::~ModoBloqueado()  {
}

void ModoBloqueado::inicializarUI()  {
    setWindowTitle( "Bloqueado" );
    resize( 400, 200 );
    setStyleSheet( "background-color: #2b1414; color: white;" );

    lMensaje = new QLabel( "<h2>Demasiados intentos fallidos</h2>" );
    lMensaje->setAlignment( Qt::AlignCenter );

    lCuenta = new QLabel;
    lCuenta->setAlignment( Qt::AlignCenter );
    lCuenta->setStyleSheet( "font-size: 28px; color: #ff8080;" );

    QVBoxLayout * lay = new QVBoxLayout;
    lay->addWidget( lMensaje );
    lay->addWidget( lCuenta );
    setLayout( lay );

    timer = new QTimer( this );
    timer->setInterval( 1000 );
}

void ModoBloqueado::conectarEventos()  {
    connect( timer, SIGNAL( timeout() ), this, SLOT( slot_tick() ) );
}

void ModoBloqueado::cargarDatos()  {
    QSettings config( "config.ini", QSettings::IniFormat );
    duracionBloqueo  = config.value( "login/duracionBloqueo", 15 ).toInt();
    segundosRestantes = duracionBloqueo;
    lCuenta->setText( QString( "%1 s" ).arg( segundosRestantes ) );
    timer->start();
}

void ModoBloqueado::validarEstado()  {
    // En esta pantalla no hay nada que validar, pero la implementamos
    // porque es obligatoria por la interfaz de Pantalla.
}

void ModoBloqueado::registrarEvento( const QString & descripcion )  {
    escribirLog( "ModoBloqueado", descripcion );
}

void ModoBloqueado::slot_tick()  {
    segundosRestantes--;
    lCuenta->setText( QString( "%1 s" ).arg( segundosRestantes ) );

    if ( segundosRestantes <= 0 )  {
        timer->stop();
        registrarEvento( "Bloqueo terminado" );
        emit desbloqueado();
    }
}

void ModoBloqueado::closeEvent( QCloseEvent * event )  {
    // No permitir cerrar manualmente
    event->ignore();
    registrarEvento( "Intento de cierre durante bloqueo (denegado)" );
}

void ModoBloqueado::keyPressEvent( QKeyEvent * event )  {
    // Ignorar todas las teclas durante el bloqueo
    event->ignore();
}

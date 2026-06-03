#include "login.h"
#include "ui_login.h"
#include "clima.h"
#include "ventana.h"

#include <QTimer>
#include <QDateTime>
#include <QSettings>

static const int MAX_INTENTOS = 3;
static const int MS_BLOQUEO   = 15000;   // 15 segundos

Login::Login( QWidget * parent )
    : Pantalla( parent ),
      ui( new Ui::Login ),
      ventana( nullptr ),
      intentosFallidos( 0 ),
      bloqueado( false )  {

    ui->setupUi( this );

    // Lee API key y ciudad desde archivo de configuración
    QSettings config( "config.ini", QSettings::IniFormat );
    QString apiKey = config.value( "clima/apikey", "" ).toString();
    QString ciudad = config.value( "clima/ciudad", "Cordoba,AR" ).toString();

    // Instancia el servicio de clima (clase derivada de QObject)
    clima = new Clima( apiKey, ciudad, this );

    // Reloj que actualiza la hora cada segundo
    relojHora = new QTimer( this );
    relojHora->setInterval( 1000 );

    // Connects (signals/slots tal como se ven en clase)
    connect( ui->pbIngresar, SIGNAL( clicked() ),
             this, SLOT( slot_validarUsuario() ) );

    connect( ui->leClave, SIGNAL( returnPressed() ),
             this, SLOT( slot_validarUsuario() ) );

    connect( clima, SIGNAL( climaListo( QString ) ),
             this, SLOT( slot_climaListo( QString ) ) );

    connect( clima, SIGNAL( errorClima( QString ) ),
             this, SLOT( slot_climaError( QString ) ) );

    connect( relojHora, SIGNAL( timeout() ),
             this, SLOT( slot_actualizarHora() ) );

    registrarEvento( "Login: ventana inicializada" );
}

Login::~Login()  {
    delete ui;
}

void Login::mostrar()  {
    this->show();
    clima->consultarClima();     // dispara la consulta inicial al clima
    relojHora->start();
    slot_actualizarHora();
    registrarEvento( "Login: pantalla mostrada" );
}

void Login::cerrar()  {
    relojHora->stop();
    this->close();
    registrarEvento( "Login: pantalla cerrada" );
}

void Login::slot_validarUsuario()  {
    if ( bloqueado )  {
        ui->lMensaje->setText( "Bloqueado. Esperá unos segundos." );
        return;
    }

    QString u = ui->leUsuario->text();
    QString c = ui->leClave->text();

    if ( u == "admin" && c == "1234" )  {
        registrarEvento( "Login: acceso correcto" );
        this->setAttribute( Qt::WA_QuitOnClose, false );

        // Abre la ventana principal (que esperará a que su imagen termine de bajar)
        ventana = new Ventana( nullptr );
        ventana->mostrar();

        this->cerrar();
    }
    else  {
        intentosFallidos++;
        registrarEvento( QString( "Login: intento fallido %1" ).arg( intentosFallidos ) );

        ui->leClave->clear();
        ui->leClave->setFocus();

        if ( intentosFallidos >= MAX_INTENTOS )  {
            bloqueado = true;
            ui->pbIngresar->setEnabled( false );
            ui->lMensaje->setText( "Demasiados intentos. Bloqueado por 15 s." );

            QTimer::singleShot( MS_BLOQUEO, this, SLOT( slot_desbloquear() ) );
            registrarEvento( "Login: bloqueo temporal activado" );
        }
        else  {
            ui->lMensaje->setText(
                QString( "Usuario o clave incorrectos (intento %1 de %2)" )
                    .arg( intentosFallidos ).arg( MAX_INTENTOS )
            );
        }
    }
}

void Login::slot_climaListo( const QString & info )  {
    ui->lClima->setText( info );
    registrarEvento( "Login: clima recibido OK" );
}

void Login::slot_climaError( const QString & motivo )  {
    ui->lClima->setText( "Modo offline (clima simulado)" );
    registrarEvento( "Login: error de clima -> " + motivo );
}

void Login::slot_desbloquear()  {
    bloqueado = false;
    intentosFallidos = 0;
    ui->pbIngresar->setEnabled( true );
    ui->lMensaje->setText( "Bloqueo terminado. Probá de nuevo." );
    registrarEvento( "Login: desbloqueado" );
}

void Login::slot_actualizarHora()  {
    QString hora = QDateTime::currentDateTime().toString( "dd/MM/yyyy hh:mm:ss" );
    ui->lHora->setText( hora );
}

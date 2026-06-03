#include "login.h"
#include "ui_login.h"

#include <QCloseEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSettings>

Login::Login( QWidget * parent )
    : Pantalla( parent ),
      ui( new Ui::Login ),
      intentosFallidos( 0 ),
      maxIntentos( 3 )  {

    inicializarUI();
    cargarDatos();
    conectarEventos();
    registrarEvento( "Ventana de Login inicializada" );
}

Login::~Login()  {
    delete ui;
}

void Login::inicializarUI()  {
    ui->setupUi( this );
}

void Login::conectarEventos()  {
    connect( ui->pbIngresar, SIGNAL( clicked() ),
             this, SLOT( slot_validarUsuario() ) );

    connect( ui->leClave, SIGNAL( returnPressed() ),
             this, SLOT( slot_validarUsuario() ) );
}

void Login::cargarDatos()  {
    QSettings config( "config.ini", QSettings::IniFormat );
    usuarioConfigurado = config.value( "login/usuario", "admin" ).toString();
    claveConfigurada   = config.value( "login/clave",   "1234"  ).toString();
    maxIntentos        = config.value( "login/maxIntentos", 3 ).toInt();
}

void Login::validarEstado()  {
    // Habilita / deshabilita el botón según haya texto cargado
    bool listo = ! ui->leUsuario->text().isEmpty() &&
                 ! ui->leClave->text().isEmpty();
    ui->pbIngresar->setEnabled( listo );
}

void Login::registrarEvento( const QString & descripcion )  {
    escribirLog( "Login", descripcion );
}

void Login::slot_validarUsuario()  {
    QString u = ui->leUsuario->text();
    QString c = ui->leClave->text();

    if ( u == usuarioConfigurado && c == claveConfigurada )  {
        registrarEvento( "Acceso correcto" );
        emit loginExitoso();
    }
    else  {
        intentosFallidos++;
        ui->leClave->clear();
        ui->leClave->setFocus();

        registrarEvento( QString( "Intento fallido %1" ).arg( intentosFallidos ) );

        if ( intentosFallidos >= maxIntentos )  {
            registrarEvento( "Demasiados intentos => bloqueo" );
            emit demasiadosIntentos();
        }
        else  {
            ui->lMensaje->setText(
                QString( "Usuario o clave incorrectos (%1/%2)" )
                    .arg( intentosFallidos ).arg( maxIntentos )
            );
        }
    }
}

void Login::closeEvent( QCloseEvent * event )  {
    auto resp = QMessageBox::question(
        this, "Salir",
        "¿Salir de la aplicación?",
        QMessageBox::Yes | QMessageBox::No
    );

    if ( resp == QMessageBox::Yes )  {
        registrarEvento( "Cerrado por usuario" );
        event->accept();
    }
    else  {
        event->ignore();
    }
}

void Login::keyPressEvent( QKeyEvent * event )  {
    if ( event->key() == Qt::Key_Escape )  {
        close();
        return;
    }
    Pantalla::keyPressEvent( event );
}

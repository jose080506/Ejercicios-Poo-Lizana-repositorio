#include "login.h"
#include "ui_login.h"
#include "adminarchivos.h"

Login::Login( AdminArchivos * admin, QWidget * parent )
    : QWidget( parent ),
      ui( new Ui::Login ),
      admin( admin )  {

    ui->setupUi( this );

    connect( ui->pbIngresar, SIGNAL( clicked() ),
             this, SLOT( slot_validar() ) );

    connect( ui->leClave, SIGNAL( returnPressed() ),
             this, SLOT( slot_validar() ) );
}

Login::~Login()  {
    delete ui;
}

void Login::slot_validar()  {
    QString u = ui->leUsuario->text();
    QString c = ui->leClave->text();

    if ( admin->validarUsuario( u, c ) )  {
        admin->guardarSesion( u );
        admin->registrarAccion( u, "Login OK" );
        ui->lMensaje->setStyleSheet( "color: rgb(20, 160, 20);" );
        ui->lMensaje->setText( "Acceso correcto." );
        emit loginExitoso( u );
    }
    else  {
        admin->registrarAccion( u, "Login fallido" );
        ui->lMensaje->setStyleSheet( "color: rgb(200, 30, 30);" );
        ui->lMensaje->setText( "Usuario o clave incorrectos." );
        ui->leClave->clear();
        ui->leClave->setFocus();
    }
}

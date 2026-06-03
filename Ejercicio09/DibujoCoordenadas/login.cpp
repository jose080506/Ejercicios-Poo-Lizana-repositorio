#include "login.h"
#include "ui_login.h"
#include "admindb.h"

Login::Login( AdminDB * adminDB, QWidget * parent )
    : QWidget( parent ),
      ui( new Ui::Login ),
      adminDB( adminDB )  {

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
    QString usuario = ui->leUsuario->text();
    QString clave   = ui->leClave->text();

    bool valido = adminDB->validarUsuario( usuario, clave );

    if ( valido )  {
        adminDB->registrarLog( "acceso_ok", usuario );
        ui->lMensaje->setStyleSheet( "color: rgb(20, 160, 20);" );
        ui->lMensaje->setText( "Acceso correcto." );
        emit loginExitoso( usuario );
    }
    else  {
        // IMPORTANTE: registramos solo el usuario, nunca la clave.
        adminDB->registrarLog( "intento_fallido", usuario );
        ui->lMensaje->setStyleSheet( "color: rgb(200, 30, 30);" );
        ui->lMensaje->setText( "Usuario o clave incorrectos." );
        ui->leClave->clear();
        ui->leClave->setFocus();
    }
}

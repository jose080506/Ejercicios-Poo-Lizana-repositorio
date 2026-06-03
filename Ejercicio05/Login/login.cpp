#include "login.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

Login::Login( QWidget * parent ) : QWidget( parent )  {

    setWindowTitle( "Login" );
    resize( 320, 180 );

    QLabel * label_titulo  = new QLabel( "<h2>Iniciar sesión</h2>" );
    QLabel * label_usuario = new QLabel( "Usuario:" );
    QLabel * label_clave   = new QLabel( "Clave:" );

    usuario = new QLineEdit;
    clave   = new QLineEdit;
    clave->setEchoMode( QLineEdit::Password );

    boton_ingresar = new QPushButton( "Ingresar" );

    mensaje = new QLabel;
    mensaje->setStyleSheet( "color: red;" );

    QGridLayout * layout = new QGridLayout;
    layout->addWidget( label_titulo,    0, 0, 1, 2 );
    layout->addWidget( label_usuario,   1, 0 );
    layout->addWidget( usuario,         1, 1 );
    layout->addWidget( label_clave,     2, 0 );
    layout->addWidget( clave,           2, 1 );
    layout->addWidget( boton_ingresar,  3, 0, 1, 2 );
    layout->addWidget( mensaje,         4, 0, 1, 2 );

    setLayout( layout );

    connect( boton_ingresar, SIGNAL( clicked() ),
             this, SLOT( slot_validar() ) );

    connect( clave, SIGNAL( returnPressed() ),
             this, SLOT( slot_validar() ) );
}

void Login::slot_validar()  {
    QString u = usuario->text();
    QString c = clave->text();

    if ( u == "admin" && c == "1234" )  {
        mensaje->setStyleSheet( "color: green;" );
        mensaje->setText( "Acceso correcto." );
    }
    else  {
        mensaje->setStyleSheet( "color: red;" );
        mensaje->setText( "Usuario o clave incorrectos." );
        clave->clear();
        clave->setFocus();
    }
}

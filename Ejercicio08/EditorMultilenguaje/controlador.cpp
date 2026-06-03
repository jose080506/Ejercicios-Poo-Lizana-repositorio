#include "controlador.h"

#include "pantalla.h"
#include "login.h"
#include "editorprincipal.h"
#include "modobloqueado.h"

Controlador::Controlador( QObject * parent )
    : QObject( parent ),
      actual( nullptr )  {
}

Controlador::~Controlador()  {
    delete actual;
}

void Controlador::iniciar()  {
    // Arranca con el Login
    Login * login = new Login;
    connect( login, SIGNAL( loginExitoso() ),
             this, SLOT( slot_loginExitoso() ) );
    connect( login, SIGNAL( demasiadosIntentos() ),
             this, SLOT( slot_demasiadosIntentos() ) );

    cambiarA( login );
}

void Controlador::cambiarA( Pantalla * nueva )  {
    // El polimorfismo en acción: trabajamos contra Pantalla *
    Pantalla * vieja = actual;
    actual = nueva;
    actual->show();

    if ( vieja )  {
        // Evitar que la app se cierre al ocultar la pantalla anterior
        vieja->setAttribute( Qt::WA_QuitOnClose, false );
        vieja->hide();
        vieja->deleteLater();
    }
}

void Controlador::slot_loginExitoso()  {
    EditorPrincipal * editor = new EditorPrincipal;
    cambiarA( editor );
    editor->showFullScreen();   // full screen como pide la consigna
}

void Controlador::slot_demasiadosIntentos()  {
    ModoBloqueado * bloq = new ModoBloqueado;
    connect( bloq, SIGNAL( desbloqueado() ),
             this, SLOT( slot_desbloqueado() ) );
    cambiarA( bloq );
}

void Controlador::slot_desbloqueado()  {
    // Volver al Login
    Login * login = new Login;
    connect( login, SIGNAL( loginExitoso() ),
             this, SLOT( slot_loginExitoso() ) );
    connect( login, SIGNAL( demasiadosIntentos() ),
             this, SLOT( slot_demasiadosIntentos() ) );
    cambiarA( login );
}

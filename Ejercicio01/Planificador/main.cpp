#include <QApplication>
#include "adminarchivos.h"
#include "login.h"
#include "planificador.h"

int main( int argc, char ** argv )  {
    QApplication app( argc, argv );

    AdminArchivos admin;

    // ¿Hay una sesión viva de los últimos 5 minutos?
    QString usuarioSesion = admin.sesionActiva();
    if ( ! usuarioSesion.isEmpty() )  {
        Planificador * tablero = new Planificador( &admin, usuarioSesion );
        tablero->setAttribute( Qt::WA_DeleteOnClose );
        tablero->show();
        return app.exec();
    }

    // Sin sesión: mostrar Login
    Login login( &admin );
    login.show();

    Planificador * tablero = nullptr;

    QObject::connect( &login, &Login::loginExitoso,
                      [ &login, &tablero, &admin ]( const QString & usuario )  {
        tablero = new Planificador( &admin, usuario );
        tablero->setAttribute( Qt::WA_DeleteOnClose );
        tablero->show();
        login.close();
    } );

    return app.exec();
}

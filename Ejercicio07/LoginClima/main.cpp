#include <QApplication>
#include <QNetworkProxyFactory>
#include "login.h"

int main( int argc, char ** argv )  {
    QApplication app( argc, argv );

    // Soporte de proxy del sistema (Chrome / Edge lo respetan)
    QNetworkProxyFactory::setUseSystemConfiguration( true );

    Login login;
    login.mostrar();   // método virtual heredado de Pantalla

    return app.exec();
}

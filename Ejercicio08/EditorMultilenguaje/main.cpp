#include <QApplication>
#include "controlador.h"

int main( int argc, char ** argv )  {
    QApplication app( argc, argv );

    Controlador controlador;
    controlador.iniciar();

    return app.exec();
}

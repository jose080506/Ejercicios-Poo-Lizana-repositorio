#include <QApplication>
#include "juego.h"

int main( int argc, char ** argv )  {
    QApplication app( argc, argv );

    Juego juego;
    juego.show();

    return app.exec();
}

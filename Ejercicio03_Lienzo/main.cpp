#include "Ventana.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("Fusion");   // base limpia para el estilo Metro

    Ventana ventana;
    ventana.show();

    return app.exec();
}

#include "pantalla.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>

QString Pantalla::rutaLog = "eventos.log";

Pantalla::Pantalla( QWidget * parent ) : QWidget( parent )  {
}

Pantalla::~Pantalla()  {
}

void Pantalla::registrarEvento( const QString & descripcion )  {
    QFile archivo( rutaLog );

    if ( ! archivo.open( QIODevice::Append | QIODevice::Text ) )  {
        return;
    }

    QTextStream out( &archivo );
    QString fecha = QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" );
    out << "[" << fecha << "] " << descripcion << "\n";

    archivo.close();
}

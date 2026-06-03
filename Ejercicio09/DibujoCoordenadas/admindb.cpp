#include "admindb.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDateTime>
#include <QDebug>

AdminDB::AdminDB( QObject * parent ) : QObject( parent )  {
    db = QSqlDatabase::addDatabase( "QSQLITE" );
}

bool AdminDB::conectar( const QString & archivoSqlite )  {
    db.setDatabaseName( archivoSqlite );

    if ( db.open() )  {
        qDebug() << "Conexión exitosa a" << archivoSqlite;
        return true;
    }

    qDebug() << "No se pudo abrir la base:" << db.lastError().text();
    return false;
}

QSqlDatabase AdminDB::getDB()  {
    return db;
}

bool AdminDB::validarUsuario( const QString & usuario, const QString & clave )  {
    if ( ! db.isOpen() )  return false;

    QSqlQuery query( db );
    query.exec(
        "SELECT nombre, apellido FROM usuarios WHERE usuario='" +
        usuario + "' AND clave='" + clave + "'"
    );

    while ( query.next() )  {
        QSqlRecord record = query.record();
        int columnaNombre = record.indexOf( "nombre" );
        int columnaApellido = record.indexOf( "apellido" );

        qDebug() << "Nombre="    << query.value( columnaNombre ).toString();
        qDebug() << "Apellido="  << query.value( columnaApellido ).toString();

        return true;
    }

    return false;
}

void AdminDB::registrarLog( const QString & tipo, const QString & usuario )  {
    if ( ! db.isOpen() )  return;

    QString fecha = QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" );

    QSqlQuery query( db );
    bool ok = query.exec(
        "INSERT INTO logs (fecha, tipo, usuario) VALUES ('" +
        fecha + "', '" + tipo + "', '" + usuario + "')"
    );

    if ( ! ok )  {
        qDebug() << "Error al registrar log:" << query.lastError().text();
    }
}

void AdminDB::guardarPunto( qint64 sesion, int trazo, int orden,
                            int x, int y,
                            const QColor & color, int grosor,
                            bool esInicio )  {
    if ( ! db.isOpen() )  return;

    QString colorStr = color.name();   // formato "#RRGGBB"

    QSqlQuery query( db );
    bool ok = query.exec(
        QString( "INSERT INTO trazos "
                 "(sesion, trazo, orden, x, y, color, grosor, es_inicio) "
                 "VALUES (%1, %2, %3, %4, %5, '%6', %7, %8)" )
            .arg( sesion ).arg( trazo ).arg( orden )
            .arg( x ).arg( y )
            .arg( colorStr ).arg( grosor )
            .arg( esInicio ? 1 : 0 )
    );

    if ( ! ok )  {
        qDebug() << "Error al guardar punto:" << query.lastError().text();
    }
}

int AdminDB::cantidadTrazos( qint64 sesion )  {
    if ( ! db.isOpen() )  return 0;

    QSqlQuery query( db );
    query.exec( QString( "SELECT COUNT(DISTINCT trazo) FROM trazos WHERE sesion=%1" )
                    .arg( sesion ) );

    if ( query.next() )  {
        return query.value( 0 ).toInt();
    }
    return 0;
}

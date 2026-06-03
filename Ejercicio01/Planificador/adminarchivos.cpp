#include "adminarchivos.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QStringList>

AdminArchivos::AdminArchivos( QObject * parent ) : QObject( parent ),
    rutaUsuarios( "users.csv" ),
    rutaTPs( "tps.csv" ),
    rutaSesion( "sesion.dat" ),
    rutaHistorial( "historial.log" )  {

    crearUsuariosPorDefectoSiNoExisten();
}

// ============= Usuarios =============

void AdminArchivos::crearUsuariosPorDefectoSiNoExisten()  {
    QFile f( rutaUsuarios );
    if ( f.exists() )  return;

    if ( ! f.open( QIODevice::WriteOnly | QIODevice::Text ) )  return;
    QTextStream out( &f );
    out << "usuario,clave,nombre\n";
    out << "admin,1234,Administrador\n";
    out << "jose,qwerty,José Pérez\n";
    f.close();
}

bool AdminArchivos::validarUsuario( const QString & usuario, const QString & clave )  {
    QFile f( rutaUsuarios );
    if ( ! f.open( QIODevice::ReadOnly | QIODevice::Text ) )  return false;

    QTextStream in( &f );
    in.readLine();    // header

    while ( ! in.atEnd() )  {
        QStringList partes = in.readLine().split( ',' );
        if ( partes.size() < 2 )  continue;
        if ( partes[ 0 ] == usuario && partes[ 1 ] == clave )  {
            f.close();
            return true;
        }
    }
    f.close();
    return false;
}

// ============= Sesión 5 minutos =============

void AdminArchivos::guardarSesion( const QString & usuario )  {
    QFile f( rutaSesion );
    if ( ! f.open( QIODevice::WriteOnly | QIODevice::Text ) )  return;

    qint64 ms = QDateTime::currentMSecsSinceEpoch();
    QTextStream out( &f );
    out << usuario << "\n" << ms << "\n";
    f.close();
}

QString AdminArchivos::sesionActiva()  {
    QFile f( rutaSesion );
    if ( ! f.exists() )  return "";
    if ( ! f.open( QIODevice::ReadOnly | QIODevice::Text ) )  return "";

    QTextStream in( &f );
    QString usuario = in.readLine();
    qint64  ms      = in.readLine().toLongLong();
    f.close();

    qint64 ahora = QDateTime::currentMSecsSinceEpoch();
    if ( ahora - ms < SESION_MS )  return usuario;

    return "";   // expirada
}

void AdminArchivos::cerrarSesion()  {
    QFile::remove( rutaSesion );
}

// ============= TPs (CSV) =============

QList< TP > AdminArchivos::cargarTPs()  {
    QList< TP > lista;

    QFile f( rutaTPs );
    if ( ! f.exists() )  return lista;
    if ( ! f.open( QIODevice::ReadOnly | QIODevice::Text ) )  return lista;

    QTextStream in( &f );
    in.readLine();    // header

    while ( ! in.atEnd() )  {
        // Formato: id|titulo|materia|fecha|prioridad|estado|notas
        // Usamos '|' para no chocar con comas dentro de las notas.
        QStringList partes = in.readLine().split( '|' );
        if ( partes.size() < 7 )  continue;

        TP tp;
        tp.id            = partes[ 0 ].toInt();
        tp.titulo        = partes[ 1 ];
        tp.materia       = partes[ 2 ];
        tp.fechaEntrega  = QDate::fromString( partes[ 3 ], "yyyy-MM-dd" );
        tp.prioridad     = partes[ 4 ];
        tp.estado        = partes[ 5 ];
        // Las notas pueden tener saltos de línea reemplazados por "\\n"
        tp.notas         = partes[ 6 ];
        tp.notas.replace( "\\n", "\n" );

        lista.append( tp );
    }
    f.close();
    return lista;
}

bool AdminArchivos::guardarTPs( const QList< TP > & tps )  {
    QFile f( rutaTPs );
    if ( ! f.open( QIODevice::WriteOnly | QIODevice::Text ) )  return false;

    QTextStream out( &f );
    out << "id|titulo|materia|fecha|prioridad|estado|notas\n";

    for ( const TP & tp : tps )  {
        QString notas = tp.notas;
        notas.replace( "\n", "\\n" );
        notas.replace( "|", "/" );    // por las dudas
        out << tp.id            << "|"
            << tp.titulo        << "|"
            << tp.materia       << "|"
            << tp.fechaEntrega.toString( "yyyy-MM-dd" ) << "|"
            << tp.prioridad     << "|"
            << tp.estado        << "|"
            << notas << "\n";
    }
    f.close();
    return true;
}

int AdminArchivos::nextId( const QList< TP > & tps )  {
    int max = 0;
    for ( const TP & tp : tps )  {
        if ( tp.id > max )  max = tp.id;
    }
    return max + 1;
}

// ============= Historial =============

void AdminArchivos::registrarAccion( const QString & usuario, const QString & accion )  {
    QFile f( rutaHistorial );
    if ( ! f.open( QIODevice::Append | QIODevice::Text ) )  return;

    QTextStream out( &f );
    QString fecha = QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" );
    out << "[" << fecha << "] " << usuario << " => " << accion << "\n";
    f.close();
}

QStringList AdminArchivos::cargarHistorial( int ultimas )  {
    QStringList lineas;

    QFile f( rutaHistorial );
    if ( ! f.exists() )  return lineas;
    if ( ! f.open( QIODevice::ReadOnly | QIODevice::Text ) )  return lineas;

    QTextStream in( &f );
    while ( ! in.atEnd() )  lineas.append( in.readLine() );
    f.close();

    // Devolver las últimas N en orden cronológico inverso (más reciente arriba)
    QStringList ultimasLineas = lineas.mid( qMax( 0, lineas.size() - ultimas ) );
    std::reverse( ultimasLineas.begin(), ultimasLineas.end() );
    return ultimasLineas;
}

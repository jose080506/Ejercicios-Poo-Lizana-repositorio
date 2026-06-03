#ifndef ADMINARCHIVOS_H
#define ADMINARCHIVOS_H

#include <QObject>
#include <QString>
#include <QList>
#include "tp.h"

// AdminArchivos: encapsula toda la persistencia local en archivos.
//   - users.csv:      usuarios y claves
//   - tps.csv:        trabajos prácticos
//   - sesion.dat:     usuario logueado + timestamp (sesión de 5 min)
//   - historial.log:  registro de acciones

class AdminArchivos : public QObject  {
    Q_OBJECT

public:
    AdminArchivos( QObject * parent = nullptr );

    // ----- Usuarios -----
    bool validarUsuario( const QString & usuario, const QString & clave );
    void crearUsuariosPorDefectoSiNoExisten();

    // ----- Sesión 5 min -----
    void guardarSesion( const QString & usuario );
    QString sesionActiva();    // devuelve usuario si la sesión sigue viva, "" si no
    void cerrarSesion();

    // ----- TPs -----
    QList< TP > cargarTPs();
    bool guardarTPs( const QList< TP > & tps );
    int  nextId( const QList< TP > & tps );

    // ----- Historial -----
    void registrarAccion( const QString & usuario, const QString & accion );
    QStringList cargarHistorial( int ultimas = 50 );

private:
    static const int SESION_MS = 5 * 60 * 1000;   // 5 minutos en ms

    QString rutaUsuarios;
    QString rutaTPs;
    QString rutaSesion;
    QString rutaHistorial;
};

#endif // ADMINARCHIVOS_H

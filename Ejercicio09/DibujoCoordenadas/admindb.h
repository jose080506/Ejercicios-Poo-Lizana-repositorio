#ifndef ADMINDB_H
#define ADMINDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>
#include <QColor>

// AdminDB: encapsula la conexión SQLite y todas las operaciones
// de la aplicación contra la base.
//
// Tablas esperadas:
//   - usuarios (id, usuario, clave, nombre, apellido)
//   - logs    (id, fecha, tipo, usuario)
//   - trazos  (id, sesion, trazo, orden, x, y, color, grosor, es_inicio)

class AdminDB : public QObject  {
    Q_OBJECT

public:
    AdminDB( QObject * parent = nullptr );

    bool conectar( const QString & archivoSqlite );
    QSqlDatabase getDB();

    // Devuelve true si el par usuario/clave existe en la tabla usuarios.
    bool validarUsuario( const QString & usuario, const QString & clave );

    // Registra un log. tipo = "acceso_ok" | "intento_fallido"
    // IMPORTANTE: nunca se guarda la clave.
    void registrarLog( const QString & tipo, const QString & usuario );

    // Persiste un punto del dibujo.
    // sesion: identificador único de la corrida actual (timestamp)
    // trazo: nro de trazo dentro de la sesión (un trazo = un movimiento continuo)
    // orden: nro de punto dentro del trazo
    // esInicio: 1 si es el primer punto del trazo, 0 si es continuación
    void guardarPunto( qint64 sesion, int trazo, int orden,
                       int x, int y,
                       const QColor & color, int grosor,
                       bool esInicio );

    // Cantidad de trazos persistidos en la sesión actual
    int cantidadTrazos( qint64 sesion );

private:
    QSqlDatabase db;
};

#endif // ADMINDB_H

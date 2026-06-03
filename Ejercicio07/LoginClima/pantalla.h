#ifndef PANTALLA_H
#define PANTALLA_H

#include <QWidget>
#include <QString>

// Clase base abstracta. Interfaz común de cualquier pantalla del sistema.
// Tiene métodos virtuales puros => no se puede instanciar directamente.
// Login y Ventana heredan de acá.

class Pantalla : public QWidget  {
    Q_OBJECT

public:
    Pantalla( QWidget * parent = nullptr );
    virtual ~Pantalla();

    // Interfaz común (virtual pura)
    virtual void mostrar() = 0;
    virtual void cerrar() = 0;

    // Método común a todas las derivadas: log de eventos a archivo
    void registrarEvento( const QString & descripcion );

protected:
    static QString rutaLog;   // ruta del archivo de log compartido
};

#endif // PANTALLA_H

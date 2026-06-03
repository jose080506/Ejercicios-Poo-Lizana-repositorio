#ifndef PANTALLA_H
#define PANTALLA_H

#include <QWidget>
#include <QString>

// Clase base abstracta. Define la interfaz común que toda pantalla
// del sistema debe implementar. Todas las funciones son virtuales puras
// => imposible instanciar esta clase directamente.

class Pantalla : public QWidget  {
    Q_OBJECT

public:
    Pantalla( QWidget * parent = nullptr );
    virtual ~Pantalla();

    // Interfaz común (5 virtuales puras, obligatorias en cada derivada)
    virtual void inicializarUI() = 0;
    virtual void conectarEventos() = 0;
    virtual void cargarDatos() = 0;
    virtual void validarEstado() = 0;
    virtual void registrarEvento( const QString & descripcion ) = 0;

protected:
    // Helper compartido para escribir al log. Cada derivada lo usa desde
    // su propia implementación de registrarEvento() con un prefijo distinto.
    static void escribirLog( const QString & origen, const QString & descripcion );

    static QString rutaLog;
};

#endif // PANTALLA_H

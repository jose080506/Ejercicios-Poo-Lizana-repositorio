#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <QObject>

class Pantalla;
class Login;
class EditorPrincipal;
class ModoBloqueado;

// Controlador del flujo de pantallas. Mantiene un puntero a Pantalla *
// (clase base) y va cambiando entre las tres concretas según los eventos.
// Esto es el polimorfismo en acción: el flujo opera contra la interfaz
// abstracta, no contra las clases concretas.

class Controlador : public QObject  {
    Q_OBJECT

public:
    Controlador( QObject * parent = nullptr );
    ~Controlador();

    void iniciar();

private slots:
    void slot_loginExitoso();
    void slot_demasiadosIntentos();
    void slot_desbloqueado();

private:
    void cambiarA( Pantalla * nueva );

    Pantalla * actual;
};

#endif // CONTROLADOR_H

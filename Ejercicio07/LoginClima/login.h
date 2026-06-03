#ifndef LOGIN_H
#define LOGIN_H

#include "pantalla.h"

namespace Ui  {
    class Login;
}

class Clima;
class Ventana;
class QTimer;

class Login : public Pantalla  {
    Q_OBJECT

public:
    Login( QWidget * parent = nullptr );
    ~Login();

    // Reimplementación de la interfaz de Pantalla
    void mostrar() override;
    void cerrar() override;

private slots:
    void slot_validarUsuario();
    void slot_climaListo( const QString & info );
    void slot_climaError( const QString & motivo );
    void slot_desbloquear();
    void slot_actualizarHora();

private:
    Ui::Login * ui;

    Clima * clima;
    Ventana * ventana;
    QTimer * relojHora;

    int intentosFallidos;
    bool bloqueado;
};

#endif // LOGIN_H

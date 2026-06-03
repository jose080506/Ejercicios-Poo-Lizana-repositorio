#ifndef LOGIN_H
#define LOGIN_H

#include "pantalla.h"

namespace Ui  {
    class Login;
}

class Login : public Pantalla  {
    Q_OBJECT

public:
    Login( QWidget * parent = nullptr );
    ~Login();

    // Interfaz de Pantalla (todas obligatorias)
    void inicializarUI() override;
    void conectarEventos() override;
    void cargarDatos() override;
    void validarEstado() override;
    void registrarEvento( const QString & descripcion ) override;

signals:
    void loginExitoso();
    void demasiadosIntentos();

protected:
    // Eventos redefinidos
    void closeEvent( QCloseEvent * event ) override;
    void keyPressEvent( QKeyEvent * event ) override;

private slots:
    void slot_validarUsuario();

private:
    Ui::Login * ui;
    QString usuarioConfigurado;
    QString claveConfigurada;
    int intentosFallidos;
    int maxIntentos;
};

#endif // LOGIN_H

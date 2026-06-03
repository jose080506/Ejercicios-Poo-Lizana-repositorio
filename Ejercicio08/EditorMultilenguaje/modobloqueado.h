#ifndef MODOBLOQUEADO_H
#define MODOBLOQUEADO_H

#include "pantalla.h"

class QLabel;
class QTimer;

class ModoBloqueado : public Pantalla  {
    Q_OBJECT

public:
    ModoBloqueado( QWidget * parent = nullptr );
    ~ModoBloqueado();

    void inicializarUI() override;
    void conectarEventos() override;
    void cargarDatos() override;
    void validarEstado() override;
    void registrarEvento( const QString & descripcion ) override;

signals:
    void desbloqueado();

protected:
    // No permitir cerrar manualmente la pantalla de bloqueo
    void closeEvent( QCloseEvent * event ) override;
    void keyPressEvent( QKeyEvent * event ) override;

private slots:
    void slot_tick();

private:
    QLabel * lMensaje;
    QLabel * lCuenta;
    QTimer * timer;
    int segundosRestantes;
    int duracionBloqueo;
};

#endif // MODOBLOQUEADO_H

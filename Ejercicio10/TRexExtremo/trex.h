#ifndef TREX_H
#define TREX_H

#include <QWidget>

class QTimer;

// TRex: el dinosaurio del jugador.
// Tiene su propio QTimer interno para simular la física del salto
// (velocidad vertical + gravedad).

class TRex : public QWidget  {
    Q_OBJECT

public:
    TRex( QWidget * parent = nullptr );

    void saltar();
    void agacharse( bool sí );
    void moverHorizontal( int dx );    // adelantarse/frenarse temporal
    void reiniciar();

    // Hitbox del dinosaurio en coordenadas del padre (para colisiones).
    QRect hitbox() const;

    int yPiso() const  {  return piso;  }
    void setYPiso( int y );

protected:
    void paintEvent( QPaintEvent * event ) override;

private slots:
    void slot_fisica();

private:
    QTimer * timerFisica;
    int   velocidadY;        // velocidad vertical actual (negativa = subiendo)
    int   piso;              // posición Y del piso (y del trex cuando está parado)
    int   xBase;             // posición X normal
    bool  agachado;
    bool  enElAire;

    // Animación de patas mientras corre
    int   framePata;
};

#endif // TREX_H

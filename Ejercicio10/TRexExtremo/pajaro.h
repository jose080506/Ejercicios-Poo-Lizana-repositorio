#ifndef PAJARO_H
#define PAJARO_H

#include <QWidget>

class QTimer;

// Pajaro: obstáculo volador. TIENE SU PROPIO QTIMER (requerimiento de la consigna).
// Cada pájaro se mueve por sí solo a la izquierda, independiente del resto.
// Cuando sale por la izquierda, emite un signal para que el Juego lo elimine.

class Pajaro : public QWidget  {
    Q_OBJECT

public:
    enum Tipo { Chico = 0, Medio = 1, Grande = 2 };

    // intervaloMs: velocidad del timer del pájaro (menor = más rápido)
    // pasoPx:      cuántos píxeles se mueve cada tick
    Pajaro( Tipo tipo, int intervaloMs, int pasoPx, QWidget * parent = nullptr );

    QRect hitbox() const;

signals:
    void salioDePantalla( Pajaro * yo );

protected:
    void paintEvent( QPaintEvent * event ) override;

private slots:
    void slot_mover();
    void slot_aletear();

private:
    QTimer * timerMovimiento;
    QTimer * timerAleteo;
    int pasoPx;
    Tipo tipo;
    bool alasArriba;
};

#endif // PAJARO_H

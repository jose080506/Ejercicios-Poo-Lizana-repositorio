#ifndef CACTUS_H
#define CACTUS_H

#include <QWidget>

// Cactus: obstáculo en el piso. NO tiene timer propio: lo mueve el
// timer principal del Juego, junto con los demás cactus.

class Cactus : public QWidget  {
    Q_OBJECT

public:
    enum Tipo { Chico = 0, Medio = 1, Grande = 2, Doble = 3 };

    Cactus( Tipo tipo, QWidget * parent = nullptr );

    QRect hitbox() const;

protected:
    void paintEvent( QPaintEvent * event ) override;

private:
    Tipo tipo;
};

#endif // CACTUS_H

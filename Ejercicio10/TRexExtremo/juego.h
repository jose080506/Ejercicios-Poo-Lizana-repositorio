#ifndef JUEGO_H
#define JUEGO_H

#include <QWidget>
#include <QList>

class TRex;
class Cactus;
class Pajaro;
class QTimer;
class QLabel;

class Juego : public QWidget  {
    Q_OBJECT

public:
    Juego( QWidget * parent = nullptr );

protected:
    void keyPressEvent( QKeyEvent * event ) override;
    void keyReleaseEvent( QKeyEvent * event ) override;
    void paintEvent( QPaintEvent * event ) override;
    void resizeEvent( QResizeEvent * event ) override;

private slots:
    void slot_tick();              // timer principal: mueve cactus + colisiones
    void slot_spawnCactus();
    void slot_spawnPajaro();       // cada 5 segundos (consigna)
    void slot_aumentarDificultad();
    void slot_pajaroSalio( Pajaro * p );

private:
    void reiniciar();
    void gameOver();
    bool detectarColisiones();

    TRex   * trex;
    QLabel * lPuntaje;
    QLabel * lGameOver;

    QList< Cactus * > cactus;
    QList< Pajaro * > pajaros;

    QTimer * timerPrincipal;        // mueve cactus + detecta colisiones
    QTimer * timerSpawnCactus;
    QTimer * timerSpawnPajaro;      // 5000 ms exactos
    QTimer * timerDificultad;

    int  velocidadCactus;           // pixeles por tick que se mueven los cactus
    int  puntaje;
    bool jugando;

    int  yPiso;                     // altura del piso en píxeles
};

#endif // JUEGO_H

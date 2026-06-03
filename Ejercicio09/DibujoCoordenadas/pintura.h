#ifndef PINTURA_H
#define PINTURA_H

#include <QWidget>
#include <QPixmap>
#include <QColor>
#include <QPoint>
#include <QVector>

// Pintura: lienzo para dibujar a mano alzada con el mouse.
//
// Controles:
//   - Mouse arrastrar:   dibuja
//   - Rueda del mouse:   ajusta grosor del pincel
//   - R / G / B:         cambia color a rojo / verde / azul
//   - Escape:            borra el lienzo entero
//   - Ctrl + Z:          deshace el último trazo (hasta 10)
//
// Cada vez que se dibuja un punto, se emite un signal con sus datos
// para que MainWindow lo persista en la base.

class Pintura : public QWidget  {
    Q_OBJECT

public:
    Pintura( QWidget * parent = nullptr );

    QColor colorActual() const  {  return color;  }
    int    grosorActual() const {  return grosor; }

signals:
    void puntoDibujado( int x, int y, const QColor & color,
                        int grosor, bool esInicio );
    void estadoCambiado( const QColor & color, int grosor );
    void lienzoBorrado();
    void trazoDeshecho();

protected:
    // Eventos redefinidos
    void paintEvent( QPaintEvent * event ) override;
    void mousePressEvent( QMouseEvent * event ) override;
    void mouseMoveEvent( QMouseEvent * event ) override;
    void mouseReleaseEvent( QMouseEvent * event ) override;
    void wheelEvent( QWheelEvent * event ) override;
    void keyPressEvent( QKeyEvent * event ) override;
    void resizeEvent( QResizeEvent * event ) override;

private:
    void inicializarLienzo();
    void redibujarDesdeTrazos();

    struct Punto  {
        QPoint pos;
        QColor color;
        int    grosor;
        bool   esInicio;
    };

    QPixmap lienzo;             // buffer del dibujo
    QColor  color;              // color actual del pincel
    int     grosor;             // grosor actual

    bool    dibujando;          // mouse está apretado
    QPoint  ultimoPunto;

    QVector< QVector< Punto > > trazos;   // pila de trazos para undo (cap 10)
};

#endif // PINTURA_H

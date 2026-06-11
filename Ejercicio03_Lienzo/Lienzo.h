#ifndef LIENZO_H
#define LIENZO_H

#include "ModeloDibujo.h"

#include <QColor>
#include <QWidget>

// Vista: recibe el modelo y lo renderiza con paintEvent.
// También captura eventos de mouse/teclado/scroll y los
// traduce a operaciones sobre el modelo.
class Lienzo : public QWidget {
    Q_OBJECT

public:
    explicit Lienzo(ModeloDibujo *modelo, QWidget *parent = nullptr);

    // Color actual (interpolado según tecla 1-9)
    QColor colorActual() const { return m_colorActual; }
    int    grosorActual() const { return m_grosor; }

protected:
    void paintEvent(QPaintEvent *event)         override;
    void mousePressEvent(QMouseEvent *event)    override;
    void mouseMoveEvent(QMouseEvent *event)     override;
    void mouseReleaseEvent(QMouseEvent *event)  override;
    void wheelEvent(QWheelEvent *event)         override;
    void keyPressEvent(QKeyEvent *event)        override;

private:
    // Interpolación de color: 9 pasos entre (192,19,76) y (24,233,199)
    static QColor interpolarColor(int paso);

    // Interpolación de puntos: genera puntos intermedios para trazo suave
    static QList<QPoint> interpolar(const QPoint &desde, const QPoint &hasta,
                                    int pasos = 6);

    ModeloDibujo *m_modelo;
    QColor        m_colorActual;
    int           m_grosor  = 6;
    bool          m_dibujando = false;
    bool          m_borrando  = false;
    QPoint        m_ultimoPunto;
};

#endif // LIENZO_H

#include "pajaro.h"

#include <QPainter>
#include <QTimer>

Pajaro::Pajaro( Tipo t, int intervaloMs, int paso, QWidget * parent )
    : QWidget( parent ),
      pasoPx( paso ),
      tipo( t ),
      alasArriba( true )  {

    int w = 0, h = 0;
    switch ( tipo )  {
        case Chico:  w = 40; h = 24; break;
        case Medio:  w = 50; h = 30; break;
        case Grande: w = 60; h = 36; break;
    }
    resize( w, h );
    setAttribute( Qt::WA_TransparentForMouseEvents );

    // Timer propio de movimiento (esto es lo que pide la consigna)
    timerMovimiento = new QTimer( this );
    timerMovimiento->setInterval( intervaloMs );
    connect( timerMovimiento, SIGNAL( timeout() ), this, SLOT( slot_mover() ) );
    timerMovimiento->start();

    // Timer extra de aleteo (animación)
    timerAleteo = new QTimer( this );
    timerAleteo->setInterval( 180 );
    connect( timerAleteo, SIGNAL( timeout() ), this, SLOT( slot_aletear() ) );
    timerAleteo->start();
}

QRect Pajaro::hitbox() const  {
    return geometry().adjusted( 4, 4, -4, -4 );
}

void Pajaro::slot_mover()  {
    move( x() - pasoPx, y() );

    if ( x() + width() < 0 )  {
        // Salió por la izquierda. Avisar para que el Juego nos destruya.
        timerMovimiento->stop();
        timerAleteo->stop();
        emit salioDePantalla( this );
    }
}

void Pajaro::slot_aletear()  {
    alasArriba = ! alasArriba;
    update();
}

void Pajaro::paintEvent( QPaintEvent * /*event*/ )  {
    QPainter p( this );
    p.setRenderHint( QPainter::Antialiasing );
    p.setPen( Qt::NoPen );

    QColor gris( 90, 90, 90 );
    p.setBrush( gris );

    int w = width();
    int h = height();

    // Cuerpo
    p.drawEllipse( w/4, h/3, w/2, h/3 );
    // Cabeza
    p.drawEllipse( 3*w/4 - 4, h/4, w/4, h/2 );
    // Pico
    QPolygon pico;
    pico << QPoint( w - 2, h/2 )
         << QPoint( w + 8, h/2 + 2 )
         << QPoint( w - 2, h/2 + 4 );
    p.setBrush( QColor( 220, 180, 0 ) );
    p.drawPolygon( pico );

    // Alas (animadas)
    p.setBrush( gris );
    if ( alasArriba )  {
        QPolygon ala;
        ala << QPoint( w/3, h/2 )
            << QPoint( w/2, 0 )
            << QPoint( 2*w/3, h/2 );
        p.drawPolygon( ala );
    }
    else  {
        QPolygon ala;
        ala << QPoint( w/3, h/2 )
            << QPoint( w/2, h - 2 )
            << QPoint( 2*w/3, h/2 );
        p.drawPolygon( ala );
    }

    // Ojo
    p.setBrush( Qt::white );
    p.drawEllipse( QPoint( 3*w/4 + 4, h/2 ), 3, 3 );
    p.setBrush( Qt::black );
    p.drawEllipse( QPoint( 3*w/4 + 5, h/2 ), 1, 1 );
}

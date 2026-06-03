#include "cactus.h"

#include <QPainter>

Cactus::Cactus( Tipo t, QWidget * parent ) : QWidget( parent ), tipo( t )  {
    int w = 0, h = 0;
    switch ( tipo )  {
        case Chico:   w = 20; h = 40; break;
        case Medio:   w = 24; h = 56; break;
        case Grande:  w = 28; h = 70; break;
        case Doble:   w = 44; h = 56; break;
    }
    resize( w, h );
    setAttribute( Qt::WA_TransparentForMouseEvents );
}

QRect Cactus::hitbox() const  {
    return geometry().adjusted( 2, 2, -2, -2 );
}

void Cactus::paintEvent( QPaintEvent * /*event*/ )  {
    QPainter p( this );
    p.setRenderHint( QPainter::Antialiasing );
    p.setPen( Qt::NoPen );
    QColor verde( 40, 110, 40 );
    p.setBrush( verde );

    int w = width();
    int h = height();

    if ( tipo == Doble )  {
        // Cactus chico
        p.drawRect( 2, h/2, 12, h/2 );
        p.drawRect( 0, h/2 + h/4, 16, 6 );
        // Cactus grande
        p.drawRect( 22, 4, 16, h - 4 );
        p.drawRect( 18, h/4, 24, 8 );
    }
    else  {
        // Tronco
        p.drawRect( w/3, 0, w/3, h );
        // Brazo izquierdo
        p.drawRect( 0, h/4, w/3, 6 );
        p.drawRect( 0, h/4 - h/4, 6, h/4 );
        // Brazo derecho
        p.drawRect( 2*w/3, h/3, w/3, 6 );
        p.drawRect( w - 6, h/3 - h/5, 6, h/5 );
    }
}

#include "trex.h"

#include <QPainter>
#include <QTimer>

static const int FUERZA_SALTO = -18;    // velocidad inicial al saltar (negativa = arriba)
static const int GRAVEDAD     = 1;      // aceleración vertical
static const int ANCHO_NORMAL = 60;
static const int ALTO_NORMAL  = 64;
static const int ANCHO_AGACH  = 80;
static const int ALTO_AGACH   = 36;

TRex::TRex( QWidget * parent ) : QWidget( parent ),
    velocidadY( 0 ),
    piso( 0 ),
    xBase( 80 ),
    agachado( false ),
    enElAire( false ),
    framePata( 0 )  {

    resize( ANCHO_NORMAL, ALTO_NORMAL );
    setAttribute( Qt::WA_TransparentForMouseEvents );

    timerFisica = new QTimer( this );
    timerFisica->setInterval( 25 );
    connect( timerFisica, SIGNAL( timeout() ), this, SLOT( slot_fisica() ) );
}

void TRex::setYPiso( int y )  {
    piso = y;
    move( xBase, piso );
}

void TRex::saltar()  {
    if ( enElAire || agachado )  return;
    enElAire = true;
    velocidadY = FUERZA_SALTO;
    timerFisica->start();
}

void TRex::agacharse( bool sí )  {
    if ( enElAire )  return;
    if ( sí == agachado )  return;

    agachado = sí;
    if ( agachado )  {
        resize( ANCHO_AGACH, ALTO_AGACH );
        move( x(), piso + ( ALTO_NORMAL - ALTO_AGACH ) );
    }
    else  {
        resize( ANCHO_NORMAL, ALTO_NORMAL );
        move( x(), piso );
    }
    update();
}

void TRex::moverHorizontal( int dx )  {
    int nuevoX = x() + dx;
    if ( nuevoX < 0 )  nuevoX = 0;
    if ( parentWidget() && nuevoX + width() > parentWidget()->width() )  {
        nuevoX = parentWidget()->width() - width();
    }
    move( nuevoX, y() );
}

void TRex::reiniciar()  {
    timerFisica->stop();
    velocidadY = 0;
    enElAire = false;
    agachado = false;
    resize( ANCHO_NORMAL, ALTO_NORMAL );
    move( xBase, piso );
    update();
}

QRect TRex::hitbox() const  {
    // Hitbox un poco más chica que el rect visual, para que las colisiones
    // sean menos "injustas".
    return geometry().adjusted( 6, 6, -6, -4 );
}

void TRex::slot_fisica()  {
    int nuevaY = y() + velocidadY;
    velocidadY += GRAVEDAD;

    if ( nuevaY >= piso )  {
        nuevaY = piso;
        velocidadY = 0;
        enElAire = false;
        timerFisica->stop();
    }

    move( x(), nuevaY );

    // Animar patas mientras corre (en el piso)
    if ( ! enElAire )  framePata = ( framePata + 1 ) % 2;
    update();
}

void TRex::paintEvent( QPaintEvent * /*event*/ )  {
    QPainter p( this );
    p.setRenderHint( QPainter::Antialiasing );

    QColor verde = QColor( 80, 110, 60 );
    p.setBrush( verde );
    p.setPen( Qt::NoPen );

    if ( agachado )  {
        // Cuerpo agachado (alargado y bajo)
        p.drawRoundedRect( 4, 12, 60, 18, 6, 6 );  // cuerpo
        p.drawRect( 0, 18, 10, 14 );                // cola
        p.drawRoundedRect( 50, 6, 28, 18, 4, 4 );   // cabeza extendida
        // Patas
        p.drawRect( 18 + framePata * 4, 30, 6, 6 );
        p.drawRect( 40 - framePata * 4, 30, 6, 6 );
        // Ojo
        p.setBrush( Qt::white );
        p.drawRect( 68, 12, 4, 4 );
    }
    else  {
        // Cuerpo erguido
        p.drawRect( 6, 28, 36, 24 );             // cuerpo principal
        p.drawRoundedRect( 28, 6, 28, 28, 4, 4 ); // cabeza
        p.drawRect( 0, 32, 14, 8 );               // cola
        p.drawRect( 22, 36, 6, 12 );              // bracito
        // Patas (alternadas con la animación)
        p.drawRect( 12, 52, 8, 12 );  // pata 1
        p.drawRect( 30, 52, 8, 12 );  // pata 2
        if ( ! enElAire )  {
            // animar pie levantando
            if ( framePata == 0 )  p.drawRect( 12, 50, 8, 4 );
            else                    p.drawRect( 30, 50, 8, 4 );
        }
        // Ojo
        p.setBrush( Qt::white );
        p.drawRect( 46, 14, 4, 4 );
        p.setBrush( Qt::black );
        p.drawRect( 47, 15, 2, 2 );
        // Boca
        p.setPen( Qt::black );
        p.drawLine( 44, 26, 56, 26 );
    }
}

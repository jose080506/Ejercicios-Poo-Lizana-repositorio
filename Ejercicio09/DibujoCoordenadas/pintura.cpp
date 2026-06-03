#include "pintura.h"

#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QResizeEvent>

static const int MAX_UNDO = 10;

Pintura::Pintura( QWidget * parent )
    : QWidget( parent ),
      color( Qt::black ),
      grosor( 4 ),
      dibujando( false )  {

    setFocusPolicy( Qt::StrongFocus );    // necesario para recibir teclas
    setMouseTracking( false );
    setMinimumSize( 400, 300 );
    setAutoFillBackground( false );

    inicializarLienzo();
}

void Pintura::inicializarLienzo()  {
    lienzo = QPixmap( size().isValid() ? size() : QSize( 800, 600 ) );
    lienzo.fill( Qt::white );
    update();
}

void Pintura::paintEvent( QPaintEvent * /*event*/ )  {
    QPainter p( this );
    p.drawPixmap( 0, 0, lienzo );
}

void Pintura::mousePressEvent( QMouseEvent * event )  {
    if ( event->button() != Qt::LeftButton )  return;

    dibujando = true;
    ultimoPunto = event->pos();

    // Arrancar un nuevo trazo
    trazos.append( QVector< Punto >() );
    Punto pt = { ultimoPunto, color, grosor, true };
    trazos.last().append( pt );

    // Dibujar el punto inicial (puntito) en el lienzo
    QPainter p( &lienzo );
    p.setRenderHint( QPainter::Antialiasing );
    p.setPen( QPen( color, grosor, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin ) );
    p.drawPoint( ultimoPunto );
    update();

    emit puntoDibujado( ultimoPunto.x(), ultimoPunto.y(), color, grosor, true );
}

void Pintura::mouseMoveEvent( QMouseEvent * event )  {
    if ( ! dibujando )  return;

    QPoint p = event->pos();

    // Agregar al trazo actual
    Punto pt = { p, color, grosor, false };
    trazos.last().append( pt );

    // Dibujar la línea desde el último punto
    QPainter painter( &lienzo );
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen( QPen( color, grosor, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin ) );
    painter.drawLine( ultimoPunto, p );
    ultimoPunto = p;
    update();

    emit puntoDibujado( p.x(), p.y(), color, grosor, false );
}

void Pintura::mouseReleaseEvent( QMouseEvent * event )  {
    if ( event->button() != Qt::LeftButton )  return;

    dibujando = false;

    // Mantener la pila acotada a MAX_UNDO
    while ( trazos.size() > MAX_UNDO )  {
        trazos.removeFirst();
    }
}

void Pintura::wheelEvent( QWheelEvent * event )  {
    // angleDelta().y() positivo => rueda hacia arriba => agrandar
    int delta = event->angleDelta().y() > 0 ? 1 : -1;
    grosor = qBound( 1, grosor + delta, 60 );
    emit estadoCambiado( color, grosor );
    event->accept();
}

void Pintura::keyPressEvent( QKeyEvent * event )  {
    switch ( event->key() )  {
        case Qt::Key_R:
            color = Qt::red;
            emit estadoCambiado( color, grosor );
            break;

        case Qt::Key_G:
            color = QColor( 0, 160, 0 );    // verde más oscuro, más legible
            emit estadoCambiado( color, grosor );
            break;

        case Qt::Key_B:
            color = Qt::blue;
            emit estadoCambiado( color, grosor );
            break;

        case Qt::Key_Escape:
            trazos.clear();
            inicializarLienzo();
            emit lienzoBorrado();
            break;

        case Qt::Key_Z:
            if ( event->modifiers() & Qt::ControlModifier )  {
                if ( ! trazos.isEmpty() )  {
                    trazos.removeLast();
                    redibujarDesdeTrazos();
                    emit trazoDeshecho();
                }
            }
            break;

        default:
            QWidget::keyPressEvent( event );
            return;
    }
}

void Pintura::resizeEvent( QResizeEvent * event )  {
    // Si el lienzo es más chico que el widget, lo agrandamos sin perder lo dibujado
    if ( lienzo.width() < event->size().width() ||
         lienzo.height() < event->size().height() )  {

        QPixmap nuevo( event->size().expandedTo( lienzo.size() ) );
        nuevo.fill( Qt::white );
        QPainter p( &nuevo );
        p.drawPixmap( 0, 0, lienzo );
        lienzo = nuevo;
        update();
    }
    QWidget::resizeEvent( event );
}

void Pintura::redibujarDesdeTrazos()  {
    // Reconstruye el lienzo dibujando todos los trazos guardados.
    // Se usa después de un undo.
    lienzo.fill( Qt::white );
    QPainter p( &lienzo );
    p.setRenderHint( QPainter::Antialiasing );

    for ( const QVector< Punto > & trazo : trazos )  {
        QPoint anterior;
        bool primero = true;

        for ( const Punto & pt : trazo )  {
            p.setPen( QPen( pt.color, pt.grosor,
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin ) );
            if ( primero || pt.esInicio )  {
                p.drawPoint( pt.pos );
            }
            else  {
                p.drawLine( anterior, pt.pos );
            }
            anterior = pt.pos;
            primero = false;
        }
    }
    update();
}

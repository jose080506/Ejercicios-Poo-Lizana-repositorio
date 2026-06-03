#include "juego.h"
#include "trex.h"
#include "cactus.h"
#include "pajaro.h"

#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QLabel>
#include <QRandomGenerator>

static const int FPS_MS           = 30;      // timer principal cada 30 ms (~33 fps)
static const int INTERVALO_PAJARO = 5000;    // cada 5 seg sale un pájaro (consigna)
static const int INTERVALO_DIFI   = 8000;    // cada 8 seg sube la dificultad

Juego::Juego( QWidget * parent ) : QWidget( parent ),
    velocidadCactus( 8 ),
    puntaje( 0 ),
    jugando( true ),
    yPiso( 0 )  {

    setWindowTitle( "T-Rex Extremo" );
    resize( 1000, 400 );
    setStyleSheet( "background-color: #f7f7f7;" );
    setFocusPolicy( Qt::StrongFocus );

    yPiso = height() - 110;

    // Crear T-Rex
    trex = new TRex( this );
    trex->setYPiso( yPiso );
    trex->show();

    // Label de puntaje
    lPuntaje = new QLabel( this );
    lPuntaje->setText( "Puntaje: 0" );
    lPuntaje->setStyleSheet( "color: #333; font: bold 18px;" );
    lPuntaje->move( 20, 20 );
    lPuntaje->resize( 260, 30 );

    // Label de Game Over (oculto al inicio)
    lGameOver = new QLabel( this );
    lGameOver->setText( "<center><h1 style='color:#c00;'>GAME OVER</h1>"
                        "<p style='color:#333;'>Apretá <b>Enter</b> para reiniciar</p></center>" );
    lGameOver->setStyleSheet( "background-color: rgba(255,255,255,200); "
                              "border: 2px solid #c00; border-radius: 8px;" );
    lGameOver->resize( 360, 120 );
    lGameOver->hide();

    // Timers
    timerPrincipal = new QTimer( this );
    timerPrincipal->setInterval( FPS_MS );
    connect( timerPrincipal, SIGNAL( timeout() ), this, SLOT( slot_tick() ) );
    timerPrincipal->start();

    timerSpawnCactus = new QTimer( this );
    timerSpawnCactus->setInterval( 1500 + QRandomGenerator::global()->bounded( 1500 ) );
    connect( timerSpawnCactus, SIGNAL( timeout() ), this, SLOT( slot_spawnCactus() ) );
    timerSpawnCactus->start();

    timerSpawnPajaro = new QTimer( this );
    timerSpawnPajaro->setInterval( INTERVALO_PAJARO );
    connect( timerSpawnPajaro, SIGNAL( timeout() ), this, SLOT( slot_spawnPajaro() ) );
    timerSpawnPajaro->start();

    timerDificultad = new QTimer( this );
    timerDificultad->setInterval( INTERVALO_DIFI );
    connect( timerDificultad, SIGNAL( timeout() ), this, SLOT( slot_aumentarDificultad() ) );
    timerDificultad->start();
}

void Juego::slot_tick()  {
    if ( ! jugando )  return;

    // Mover todos los cactus
    QList< Cactus * > paraEliminar;
    for ( Cactus * c : cactus )  {
        c->move( c->x() - velocidadCactus, c->y() );
        if ( c->x() + c->width() < 0 )  paraEliminar.append( c );
    }
    for ( Cactus * c : paraEliminar )  {
        cactus.removeOne( c );
        c->deleteLater();
    }

    // Detectar colisiones
    if ( detectarColisiones() )  {
        gameOver();
        return;
    }

    // Sumar puntaje
    puntaje++;
    lPuntaje->setText( QString( "Puntaje: %1   |   Velocidad: %2" )
                           .arg( puntaje )
                           .arg( velocidadCactus ) );
}

void Juego::slot_spawnCactus()  {
    if ( ! jugando )  return;

    int tipo = QRandomGenerator::global()->bounded( 4 );
    Cactus * c = new Cactus( static_cast< Cactus::Tipo >( tipo ), this );
    c->move( width(), yPiso + 64 - c->height() );
    c->show();
    cactus.append( c );

    // Reprogramar próxima aparición con intervalo aleatorio
    int proximo = 800 + QRandomGenerator::global()->bounded( 1500 );
    timerSpawnCactus->setInterval( proximo );
}

void Juego::slot_spawnPajaro()  {
    if ( ! jugando )  return;

    int tipo = QRandomGenerator::global()->bounded( 3 );
    Pajaro::Tipo t = static_cast< Pajaro::Tipo >( tipo );

    // Velocidad del pájaro: un poco más rápido que los cactus
    int intervaloPajaro = qMax( 20, 60 - velocidadCactus * 2 );
    int pasoPx = 6 + QRandomGenerator::global()->bounded( 4 );

    Pajaro * p = new Pajaro( t, intervaloPajaro, pasoPx, this );

    // Altura aleatoria: vuela bajo (a la altura de la cabeza del trex), medio o alto
    int alturas[] = { yPiso - 10, yPiso + 10, yPiso - 60, yPiso + 30 };
    int yPaj = alturas[ QRandomGenerator::global()->bounded( 4 ) ];

    p->move( width(), yPaj );
    p->show();
    pajaros.append( p );

    connect( p, SIGNAL( salioDePantalla( Pajaro * ) ),
             this, SLOT( slot_pajaroSalio( Pajaro * ) ) );
}

void Juego::slot_pajaroSalio( Pajaro * p )  {
    pajaros.removeOne( p );
    p->deleteLater();
}

void Juego::slot_aumentarDificultad()  {
    if ( ! jugando )  return;
    velocidadCactus += 1;
    if ( velocidadCactus > 22 )  velocidadCactus = 22;
}

bool Juego::detectarColisiones()  {
    QRect hbTrex = trex->hitbox();

    for ( Cactus * c : cactus )  {
        if ( hbTrex.intersects( c->hitbox() ) )  return true;
    }
    for ( Pajaro * p : pajaros )  {
        if ( hbTrex.intersects( p->hitbox() ) )  return true;
    }
    return false;
}

void Juego::gameOver()  {
    jugando = false;
    timerPrincipal->stop();
    timerSpawnCactus->stop();
    timerSpawnPajaro->stop();
    timerDificultad->stop();

    // Eliminar todos los pájaros: cada uno tiene su propio timer y
    // si no los destruimos siguen volando como si nada después del
    // Game Over. deleteLater() también mata sus timers internos
    // porque los timers tienen al pájaro como parent.
    for ( Pajaro * p : pajaros )  p->deleteLater();
    pajaros.clear();

    // Mostrar el cartel y asegurar que el Juego tenga el foco
    // para que el Enter del usuario reinicie correctamente.
    lGameOver->move( ( width() - lGameOver->width() ) / 2,
                     ( height() - lGameOver->height() ) / 2 );
    lGameOver->show();
    lGameOver->raise();
    setFocus();
}

void Juego::reiniciar()  {
    // Limpiar cactus
    for ( Cactus * c : cactus )  c->deleteLater();
    cactus.clear();

    // Los pájaros ya fueron eliminados en gameOver(), pero por las dudas
    for ( Pajaro * p : pajaros )  p->deleteLater();
    pajaros.clear();

    trex->reiniciar();
    puntaje = 0;
    velocidadCactus = 8;
    jugando = true;

    lGameOver->hide();
    lPuntaje->setText( "Puntaje: 0" );

    timerPrincipal->start();
    timerSpawnCactus->start();
    timerSpawnPajaro->start();
    timerDificultad->start();
}

void Juego::keyPressEvent( QKeyEvent * event )  {
    if ( ! jugando )  {
        if ( event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter )  {
            reiniciar();
        }
        return;
    }

    switch ( event->key() )  {
        case Qt::Key_Space:
        case Qt::Key_Up:
            trex->saltar();
            break;
        case Qt::Key_Down:
            trex->agacharse( true );
            break;
        case Qt::Key_Right:
            trex->moverHorizontal( 25 );
            break;
        case Qt::Key_Left:
            trex->moverHorizontal( -25 );
            break;
        default:
            QWidget::keyPressEvent( event );
            return;
    }
}

void Juego::keyReleaseEvent( QKeyEvent * event )  {
    if ( event->key() == Qt::Key_Down )  {
        trex->agacharse( false );
    }
    else  {
        QWidget::keyReleaseEvent( event );
    }
}

void Juego::paintEvent( QPaintEvent * /*event*/ )  {
    QPainter p( this );
    p.setRenderHint( QPainter::Antialiasing );

    // Cielo
    p.fillRect( rect(), QColor( 247, 247, 247 ) );

    // Línea del piso
    int yLinea = yPiso + 64;
    p.setPen( QPen( QColor( 90, 90, 90 ), 2 ) );
    p.drawLine( 0, yLinea, width(), yLinea );

    // Algunas piedritas decorativas
    p.setPen( Qt::NoPen );
    p.setBrush( QColor( 150, 150, 150 ) );
    for ( int x = 30; x < width(); x += 80 )  {
        p.drawEllipse( QPoint( x + ( puntaje / 2 ) % 80, yLinea + 8 ), 2, 1 );
    }
}

void Juego::resizeEvent( QResizeEvent * event )  {
    QWidget::resizeEvent( event );
    yPiso = height() - 110;
    if ( trex )  trex->setYPiso( yPiso );
}

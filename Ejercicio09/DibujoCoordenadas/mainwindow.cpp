#include "mainwindow.h"
#include "pintura.h"
#include "admindb.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QDateTime>

MainWindow::MainWindow( AdminDB * adminDB, const QString & usuario, QWidget * parent )
    : QWidget( parent ),
      adminDB( adminDB ),
      trazoActual( 0 ),
      ordenActual( 0 ),
      usuario( usuario )  {

    setWindowTitle( "Pintura - " + usuario );
    resize( 900, 650 );

    // Id único de la sesión: timestamp Unix
    sesion = QDateTime::currentSecsSinceEpoch();

    pintura = new Pintura;
    lEstado = new QLabel;
    lEstado->setStyleSheet( "padding: 6px; background-color: #222; color: #fff;" );
    actualizarEstado( pintura->colorActual(), pintura->grosorActual() );

    QVBoxLayout * lay = new QVBoxLayout;
    lay->setContentsMargins( 0, 0, 0, 0 );
    lay->setSpacing( 0 );
    lay->addWidget( pintura, 1 );
    lay->addWidget( lEstado );
    setLayout( lay );

    // Conexiones
    connect( pintura, SIGNAL( puntoDibujado( int, int, QColor, int, bool ) ),
             this, SLOT( slot_puntoDibujado( int, int, QColor, int, bool ) ) );

    connect( pintura, SIGNAL( estadoCambiado( QColor, int ) ),
             this, SLOT( slot_estadoCambiado( QColor, int ) ) );

    connect( pintura, SIGNAL( lienzoBorrado() ),
             this, SLOT( slot_lienzoBorrado() ) );

    connect( pintura, SIGNAL( trazoDeshecho() ),
             this, SLOT( slot_trazoDeshecho() ) );

    pintura->setFocus();
}

void MainWindow::slot_puntoDibujado( int x, int y, const QColor & color,
                                     int grosor, bool esInicio )  {
    if ( esInicio )  {
        trazoActual++;
        ordenActual = 0;
    }

    adminDB->guardarPunto( sesion, trazoActual, ordenActual,
                           x, y, color, grosor, esInicio );
    ordenActual++;
}

void MainWindow::slot_estadoCambiado( const QColor & color, int grosor )  {
    actualizarEstado( color, grosor );
}

void MainWindow::slot_lienzoBorrado()  {
    // Reseteo de contadores locales (lo persistido en DB se mantiene)
    trazoActual = 0;
    ordenActual = 0;
    lEstado->setText( "Lienzo borrado. Total trazos en DB: " +
                      QString::number( adminDB->cantidadTrazos( sesion ) ) );
}

void MainWindow::slot_trazoDeshecho()  {
    lEstado->setText( "Último trazo deshecho. (No se borra de la base; "
                      "queda como historial)" );
}

void MainWindow::actualizarEstado( const QColor & color, int grosor )  {
    QString swatch = QString( "<span style='background-color:%1;'>"
                              "&nbsp;&nbsp;&nbsp;&nbsp;</span>" ).arg( color.name() );
    lEstado->setText(
        QString( "Usuario: <b>%1</b> &nbsp;&nbsp; "
                 "Color: %2 %3 &nbsp;&nbsp; "
                 "Grosor: <b>%4</b> &nbsp;&nbsp; "
                 "[R/G/B color · Rueda grosor · Esc borrar · Ctrl+Z deshacer]" )
            .arg( usuario )
            .arg( swatch )
            .arg( color.name() )
            .arg( grosor )
    );
}

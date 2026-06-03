#include "planificador.h"
#include "adminarchivos.h"
#include "dialogotp.h"
#include "editornotas.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QPlainTextEdit>
#include <QScrollArea>
#include <QMessageBox>

Planificador::Planificador( AdminArchivos * admin, const QString & usuario,
                            QWidget * parent ) : QWidget( parent ),
    admin( admin ),
    usuario( usuario )  {

    setWindowTitle( "Planificador de TPs - " + usuario );
    resize( 1000, 680 );

    armarUI();

    tps = admin->cargarTPs();
    recargarTablero();
    refrescarHistorial();
}

void Planificador::armarUI()  {
    // -------- Cabecera --------
    lBienvenida = new QLabel( "<h2>Tablero de TPs - " + usuario + "</h2>" );

    QPushButton * pbLogout = new QPushButton( "Cerrar sesión" );

    QHBoxLayout * cabecera = new QHBoxLayout;
    cabecera->addWidget( lBienvenida, 1 );
    cabecera->addWidget( pbLogout );

    // -------- Barra de acciones y filtros --------
    QPushButton * pbNuevo = new QPushButton( "+ Nuevo TP" );
    pbNuevo->setStyleSheet( "background-color: #2e7d32; color: white; padding: 6px 12px;" );

    QPushButton * pbRecargar = new QPushButton( "Recargar" );

    cbFiltroEstado = new QComboBox;
    cbFiltroEstado->addItems( { "Todos", "Pendiente", "En curso", "Entregado" } );

    cbFiltroPrioridad = new QComboBox;
    cbFiltroPrioridad->addItems( { "Todas", "Alta", "Media", "Baja" } );

    leBuscar = new QLineEdit;
    leBuscar->setPlaceholderText( "Buscar por título o materia..." );

    QHBoxLayout * barra = new QHBoxLayout;
    barra->addWidget( pbNuevo );
    barra->addWidget( pbRecargar );
    barra->addSpacing( 20 );
    barra->addWidget( new QLabel( "Estado:" ) );
    barra->addWidget( cbFiltroEstado );
    barra->addWidget( new QLabel( "Prioridad:" ) );
    barra->addWidget( cbFiltroPrioridad );
    barra->addWidget( leBuscar, 1 );

    // -------- Tablero (grilla scrollable) --------
    contenedorGrilla = new QWidget;
    grilla = new QGridLayout( contenedorGrilla );
    grilla->setAlignment( Qt::AlignTop );

    scroll = new QScrollArea;
    scroll->setWidget( contenedorGrilla );
    scroll->setWidgetResizable( true );
    scroll->setMinimumHeight( 320 );

    // -------- Historial --------
    QLabel * lHist = new QLabel( "<b>Historial de acciones</b>" );
    pteHistorial = new QPlainTextEdit;
    pteHistorial->setReadOnly( true );
    pteHistorial->setMaximumHeight( 160 );
    pteHistorial->setStyleSheet( "background-color: #1e1e1e; color: #ddd; "
                                  "font-family: 'Consolas', monospace; font-size: 11px;" );

    // -------- Layout principal --------
    QVBoxLayout * lay = new QVBoxLayout( this );
    lay->addLayout( cabecera );
    lay->addLayout( barra );
    lay->addWidget( scroll, 1 );
    lay->addWidget( lHist );
    lay->addWidget( pteHistorial );

    // -------- Connects --------
    connect( pbNuevo,    SIGNAL( clicked() ), this, SLOT( slot_nuevoTP() ) );
    connect( pbRecargar, SIGNAL( clicked() ), this, SLOT( slot_recargar() ) );
    connect( pbLogout,   SIGNAL( clicked() ), this, SLOT( slot_logout() ) );

    connect( cbFiltroEstado,    SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( slot_filtroCambiado() ) );
    connect( cbFiltroPrioridad, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( slot_filtroCambiado() ) );
    connect( leBuscar, SIGNAL( textChanged( QString ) ),
             this, SLOT( slot_filtroCambiado() ) );
}

bool Planificador::pasaFiltros( const TP & tp ) const  {
    if ( cbFiltroEstado->currentText() != "Todos" &&
         cbFiltroEstado->currentText() != tp.estado )  return false;

    if ( cbFiltroPrioridad->currentText() != "Todas" &&
         cbFiltroPrioridad->currentText() != tp.prioridad )  return false;

    QString q = leBuscar->text().trimmed();
    if ( ! q.isEmpty() )  {
        if ( ! tp.titulo.contains( q, Qt::CaseInsensitive ) &&
             ! tp.materia.contains( q, Qt::CaseInsensitive ) )  return false;
    }
    return true;
}

void Planificador::recargarTablero()  {
    // Limpiar la grilla
    QLayoutItem * item;
    while ( ( item = grilla->takeAt( 0 ) ) != nullptr )  {
        if ( item->widget() )  item->widget()->deleteLater();
        delete item;
    }

    // Header
    QStringList headers = { "Título", "Materia", "Entrega", "Prioridad", "Estado", "Acciones" };
    for ( int i = 0; i < headers.size(); ++i )  {
        QLabel * lh = new QLabel( "<b>" + headers[ i ] + "</b>" );
        lh->setStyleSheet( "padding: 6px; background-color: #333; color: white;" );
        grilla->addWidget( lh, 0, i );
    }

    // Filas
    int fila = 1;
    for ( const TP & tp : tps )  {
        if ( ! pasaFiltros( tp ) )  continue;

        // Color de fondo según prioridad
        QString color = "#fff";
        if      ( tp.prioridad == "Alta"  )  color = "#ffe6e6";
        else if ( tp.prioridad == "Media" )  color = "#fff8e1";
        else if ( tp.prioridad == "Baja"  )  color = "#e8f5e9";

        QString estilo = QString( "padding: 6px; background-color: %1; color: #222;" ).arg( color );

        QLabel * lTit  = new QLabel( tp.titulo );
        QLabel * lMat  = new QLabel( tp.materia );
        QLabel * lFec  = new QLabel( tp.fechaEntrega.toString( "dd/MM/yyyy" ) );
        QLabel * lPri  = new QLabel( tp.prioridad );
        QLabel * lEst  = new QLabel( tp.estado );
        for ( QLabel * l : { lTit, lMat, lFec, lPri, lEst } )  l->setStyleSheet( estilo );

        QPushButton * pbEd   = new QPushButton( "Editar" );
        QPushButton * pbNot  = new QPushButton( "Notas" );
        QPushButton * pbDel  = new QPushButton( "Eliminar" );

        int idTP = tp.id;
        connect( pbEd,  &QPushButton::clicked, [ this, idTP ] { slot_editarTP( idTP );   } );
        connect( pbNot, &QPushButton::clicked, [ this, idTP ] { slot_notasTP( idTP );    } );
        connect( pbDel, &QPushButton::clicked, [ this, idTP ] { slot_eliminarTP( idTP ); } );

        QWidget * cont = new QWidget;
        cont->setStyleSheet( estilo );
        QHBoxLayout * h = new QHBoxLayout( cont );
        h->setContentsMargins( 4, 2, 4, 2 );
        h->addWidget( pbEd );
        h->addWidget( pbNot );
        h->addWidget( pbDel );

        grilla->addWidget( lTit, fila, 0 );
        grilla->addWidget( lMat, fila, 1 );
        grilla->addWidget( lFec, fila, 2 );
        grilla->addWidget( lPri, fila, 3 );
        grilla->addWidget( lEst, fila, 4 );
        grilla->addWidget( cont, fila, 5 );

        fila++;
    }

    if ( fila == 1 )  {
        QLabel * lVacio = new QLabel( "<i>No hay TPs que coincidan con los filtros.</i>" );
        lVacio->setStyleSheet( "padding: 20px; color: #888;" );
        lVacio->setAlignment( Qt::AlignCenter );
        grilla->addWidget( lVacio, 1, 0, 1, 6 );
    }
}

void Planificador::refrescarHistorial()  {
    QStringList lineas = admin->cargarHistorial( 50 );
    pteHistorial->setPlainText( lineas.join( "\n" ) );
}

// ============ Slots ============

void Planificador::slot_nuevoTP()  {
    TP vacio = {};
    vacio.id = 0;
    vacio.fechaEntrega = QDate::currentDate();
    vacio.prioridad = "Media";
    vacio.estado = "Pendiente";

    DialogoTP dlg( vacio, this );
    if ( dlg.exec() != QDialog::Accepted )  return;

    TP nuevo = dlg.obtenerTP();
    if ( nuevo.titulo.trimmed().isEmpty() )  {
        QMessageBox::warning( this, "Falta título", "El TP debe tener un título." );
        return;
    }
    nuevo.id = admin->nextId( tps );
    tps.append( nuevo );
    admin->guardarTPs( tps );
    admin->registrarAccion( usuario, "Crea TP: " + nuevo.titulo );

    recargarTablero();
    refrescarHistorial();
}

void Planificador::slot_editarTP( int id )  {
    for ( int i = 0; i < tps.size(); ++i )  {
        if ( tps[ i ].id != id )  continue;

        DialogoTP dlg( tps[ i ], this );
        if ( dlg.exec() != QDialog::Accepted )  return;

        TP editado = dlg.obtenerTP();
        editado.id = id;
        // Preservar las notas (el dialog no las edita)
        editado.notas = tps[ i ].notas;
        tps[ i ] = editado;

        admin->guardarTPs( tps );
        admin->registrarAccion( usuario, "Edita TP: " + editado.titulo );

        recargarTablero();
        refrescarHistorial();
        return;
    }
}

void Planificador::slot_notasTP( int id )  {
    for ( int i = 0; i < tps.size(); ++i )  {
        if ( tps[ i ].id != id )  continue;

        EditorNotas ed( tps[ i ].titulo, tps[ i ].notas, this );
        ed.exec();

        if ( ed.fueGuardado() )  {
            tps[ i ].notas = ed.notas();
            admin->guardarTPs( tps );
            admin->registrarAccion( usuario, "Guarda notas de: " + tps[ i ].titulo );
            refrescarHistorial();
        }
        return;
    }
}

void Planificador::slot_eliminarTP( int id )  {
    for ( int i = 0; i < tps.size(); ++i )  {
        if ( tps[ i ].id != id )  continue;

        auto resp = QMessageBox::question( this, "Eliminar",
            "¿Eliminar el TP '" + tps[ i ].titulo + "'?",
            QMessageBox::Yes | QMessageBox::No );
        if ( resp != QMessageBox::Yes )  return;

        QString titulo = tps[ i ].titulo;
        tps.removeAt( i );

        admin->guardarTPs( tps );
        admin->registrarAccion( usuario, "Elimina TP: " + titulo );

        recargarTablero();
        refrescarHistorial();
        return;
    }
}

void Planificador::slot_recargar()  {
    tps = admin->cargarTPs();
    recargarTablero();
    refrescarHistorial();
}

void Planificador::slot_filtroCambiado()  {
    recargarTablero();
}

void Planificador::slot_logout()  {
    admin->registrarAccion( usuario, "Cerró sesión" );
    admin->cerrarSesion();
    close();
}

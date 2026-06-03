#include "editornotas.h"

#include <QPlainTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

EditorNotas::EditorNotas( const QString & tituloTP, const QString & notasIniciales,
                          QWidget * parent ) : QDialog( parent ),
    notasGuardadas( notasIniciales ),
    guardado( false ),
    hayCambiosSinGuardar( false )  {

    setWindowTitle( "Notas: " + tituloTP );
    resize( 500, 400 );

    editor = new QPlainTextEdit;
    editor->setPlainText( notasIniciales );

    lEstado = new QLabel( "Sin cambios" );
    lEstado->setStyleSheet( "color: #888;" );

    QPushButton * pbGuardar = new QPushButton( "Guardar" );
    QPushButton * pbCerrar  = new QPushButton( "Cerrar" );

    QHBoxLayout * botones = new QHBoxLayout;
    botones->addWidget( lEstado );
    botones->addStretch( 1 );
    botones->addWidget( pbGuardar );
    botones->addWidget( pbCerrar );

    QVBoxLayout * lay = new QVBoxLayout( this );
    lay->addWidget( editor );
    lay->addLayout( botones );

    connect( editor,    SIGNAL( textChanged() ),
             this, SLOT( slot_textoCambiado() ) );
    connect( pbGuardar, SIGNAL( clicked() ), this, SLOT( slot_guardar() ) );
    connect( pbCerrar,  SIGNAL( clicked() ), this, SLOT( accept() ) );
}

QString EditorNotas::notas() const  {
    return notasGuardadas;
}

void EditorNotas::slot_guardar()  {
    notasGuardadas = editor->toPlainText();
    guardado = true;
    hayCambiosSinGuardar = false;
    lEstado->setStyleSheet( "color: #169016;" );
    lEstado->setText( "Guardado." );
}

void EditorNotas::slot_textoCambiado()  {
    hayCambiosSinGuardar = true;
    lEstado->setStyleSheet( "color: #c08000;" );
    lEstado->setText( "Cambios sin guardar" );
}

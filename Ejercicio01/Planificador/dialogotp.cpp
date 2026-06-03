#include "dialogotp.h"

#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

DialogoTP::DialogoTP( const TP & tp, QWidget * parent ) : QDialog( parent ),
    idActual( tp.id ),
    notasActuales( tp.notas )  {

    setWindowTitle( tp.id == 0 ? "Nuevo TP" : "Editar TP" );
    resize( 420, 260 );

    leTitulo  = new QLineEdit( tp.titulo );
    leMateria = new QLineEdit( tp.materia );

    deFecha = new QDateEdit;
    deFecha->setCalendarPopup( true );
    deFecha->setDisplayFormat( "dd/MM/yyyy" );
    deFecha->setDate( tp.fechaEntrega.isValid() ? tp.fechaEntrega : QDate::currentDate() );

    cbPrioridad = new QComboBox;
    cbPrioridad->addItems( { "Alta", "Media", "Baja" } );
    cbPrioridad->setCurrentText( tp.prioridad.isEmpty() ? "Media" : tp.prioridad );

    cbEstado = new QComboBox;
    cbEstado->addItems( { "Pendiente", "En curso", "Entregado" } );
    cbEstado->setCurrentText( tp.estado.isEmpty() ? "Pendiente" : tp.estado );

    QFormLayout * form = new QFormLayout;
    form->addRow( "Título:",    leTitulo );
    form->addRow( "Materia:",   leMateria );
    form->addRow( "Entrega:",   deFecha );
    form->addRow( "Prioridad:", cbPrioridad );
    form->addRow( "Estado:",    cbEstado );

    QPushButton * pbAceptar  = new QPushButton( "Aceptar" );
    QPushButton * pbCancelar = new QPushButton( "Cancelar" );
    pbAceptar->setDefault( true );

    QHBoxLayout * botones = new QHBoxLayout;
    botones->addStretch( 1 );
    botones->addWidget( pbAceptar );
    botones->addWidget( pbCancelar );

    QVBoxLayout * lay = new QVBoxLayout( this );
    lay->addLayout( form );
    lay->addLayout( botones );

    connect( pbAceptar,  SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( pbCancelar, SIGNAL( clicked() ), this, SLOT( reject() ) );
}

TP DialogoTP::obtenerTP() const  {
    TP tp;
    tp.id           = idActual;
    tp.titulo       = leTitulo->text();
    tp.materia      = leMateria->text();
    tp.fechaEntrega = deFecha->date();
    tp.prioridad    = cbPrioridad->currentText();
    tp.estado       = cbEstado->currentText();
    tp.notas        = notasActuales;   // preservamos las notas, se editan aparte
    return tp;
}

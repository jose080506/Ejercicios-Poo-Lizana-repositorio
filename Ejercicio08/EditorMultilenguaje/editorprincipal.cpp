#include "editorprincipal.h"

#include "validadorcpp.h"
#include "validadorpython.h"
#include "validadorjava.h"

#include <QPlainTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QFocusEvent>
#include <QTextCursor>
#include <QTextBlock>
#include <QTextCharFormat>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QPainter>
#include <QSettings>

EditorPrincipal::EditorPrincipal( QWidget * parent )
    : Pantalla( parent ),
      validador( nullptr ),
      lineaPrevia( 0 )  {

    inicializarUI();
    cargarDatos();
    conectarEventos();
    registrarEvento( "Editor principal inicializado" );
}

EditorPrincipal::~EditorPrincipal()  {
    delete validador;
}

void EditorPrincipal::inicializarUI()  {
    setWindowTitle( "Editor multilenguaje" );

    // Editor de código (centro / izquierda)
    editor = new QPlainTextEdit;
    editor->setStyleSheet(
        "background-color: #1e1e1e; color: #e0e0e0; "
        "font-family: 'Consolas', 'Courier New', monospace; "
        "font-size: 13px;"
    );
    editor->setPlainText(
        "// Escribí tu código acá. La validación corre al cambiar de línea.\n"
        "\n"
    );

    // Combo de lenguaje
    cbLenguaje = new QComboBox;
    cbLenguaje->addItem( "C++" );
    cbLenguaje->addItem( "Python" );
    cbLenguaje->addItem( "Java" );

    lLenguaje = new QLabel( "Lenguaje:" );
    pbExportar = new QPushButton( "Exportar a JPG" );

    lEstado = new QLabel( "Sin errores." );
    lEstado->setStyleSheet( "color: #6f6;" );

    // Toolbar superior
    QHBoxLayout * toolbar = new QHBoxLayout;
    toolbar->addWidget( lLenguaje );
    toolbar->addWidget( cbLenguaje );
    toolbar->addStretch( 1 );
    toolbar->addWidget( pbExportar );

    // Columna del editor
    QVBoxLayout * colEditor = new QVBoxLayout;
    colEditor->addLayout( toolbar );
    colEditor->addWidget( editor, 1 );
    colEditor->addWidget( lEstado );

    // Panel de CV a la derecha
    QWidget * panelCV = new QWidget;
    panelCV->setFixedWidth( 280 );
    panelCV->setStyleSheet(
        "background-color: #f5f5f5; color: #222; "
        "border-left: 1px solid #ccc;"
    );
    armarPanelCV( panelCV );

    // Layout principal
    QHBoxLayout * root = new QHBoxLayout;
    root->addLayout( colEditor, 1 );
    root->addWidget( panelCV );
    root->setContentsMargins( 0, 0, 0, 0 );
    setLayout( root );
}

void EditorPrincipal::armarPanelCV( QWidget * contenedor )  {
    QLabel * foto = new QLabel;
    foto->setFixedSize( 140, 140 );
    foto->setStyleSheet(
        "background-color: #ddd; border-radius: 70px; color: #888;"
    );
    foto->setAlignment( Qt::AlignCenter );
    foto->setText( "Foto" );

    QLabel * nombre = new QLabel( "<h2 style='margin:0;'>José Pérez</h2>" );
    QLabel * cargo  = new QLabel(
        "<p style='color:#555; margin:4px 0;'>Estudiante de Ing. Informática</p>"
    );
    QLabel * desc = new QLabel(
        "<p>Desarrollador full-stack. Qt/C++, FastAPI, React. "
        "Construyo software para PyMEs argentinas.</p>"
    );
    desc->setWordWrap( true );

    QLabel * habilidades = new QLabel(
        "<h3 style='margin:8px 0;'>Habilidades</h3>"
        "<ul style='margin:0;'>"
        "<li>C++ / Qt</li>"
        "<li>Python / FastAPI</li>"
        "<li>React / TypeScript</li>"
        "<li>SQL / Supabase</li>"
        "</ul>"
    );

    QLabel * contacto = new QLabel(
        "<h3 style='margin:8px 0;'>Contacto</h3>"
        "<p>jose080506@gmail.com<br>"
        "linkedin.com/in/jose-perez</p>"
    );

    QVBoxLayout * lay = new QVBoxLayout( contenedor );
    lay->setContentsMargins( 16, 16, 16, 16 );
    lay->addWidget( foto, 0, Qt::AlignHCenter );
    lay->addWidget( nombre );
    lay->addWidget( cargo );
    lay->addWidget( desc );
    lay->addWidget( habilidades );
    lay->addWidget( contacto );
    lay->addStretch( 1 );
}

void EditorPrincipal::conectarEventos()  {
    connect( cbLenguaje, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( slot_cambiarLenguaje( int ) ) );

    connect( pbExportar, SIGNAL( clicked() ),
             this, SLOT( slot_exportarJpg() ) );

    // Se dispara cuando el cursor cambia de posición (eventualmente de línea)
    connect( editor, SIGNAL( cursorPositionChanged() ),
             this, SLOT( slot_lineaCambiada() ) );
}

void EditorPrincipal::cargarDatos()  {
    QSettings config( "config.ini", QSettings::IniFormat );
    QString lenguajeDefault = config.value( "editor/lenguaje", "C++" ).toString();
    rutaExportacion = config.value( "editor/rutaExportacion", "codigo.jpg" ).toString();

    int idx = cbLenguaje->findText( lenguajeDefault );
    if ( idx < 0 )  idx = 0;
    cbLenguaje->setCurrentIndex( idx );
    slot_cambiarLenguaje( idx );    // instancia el validador inicial
}

void EditorPrincipal::validarEstado()  {
    // Re-valida la línea actual. Lo usamos al perder foco.
    validarLineaActual();
}

void EditorPrincipal::registrarEvento( const QString & descripcion )  {
    escribirLog( "EditorPrincipal", descripcion );
}

void EditorPrincipal::slot_cambiarLenguaje( int indice )  {
    delete validador;

    switch ( indice )  {
        case 0:  validador = new ValidadorCpp( this );    break;
        case 1:  validador = new ValidadorPython( this ); break;
        case 2:  validador = new ValidadorJava( this );   break;
        default: validador = new ValidadorCpp( this );    break;
    }

    registrarEvento( "Lenguaje cambiado a " + validador->nombreLenguaje() );
    validarLineaActual();
}

void EditorPrincipal::slot_lineaCambiada()  {
    int lineaActual = editor->textCursor().blockNumber();
    if ( lineaActual != lineaPrevia )  {
        // El usuario abandonó la línea previa => validarla ahora
        QTextBlock bloque = editor->document()->findBlockByNumber( lineaPrevia );
        if ( bloque.isValid() && validador )  {
            QString texto = bloque.text();
            bool ok = validador->validarLinea( texto );
            if ( ! ok )  {
                lEstado->setStyleSheet( "color: #f66;" );
                lEstado->setText(
                    QString( "Línea %1: %2" )
                        .arg( lineaPrevia + 1 )
                        .arg( validador->mensajeError() )
                );
                // Resaltar la línea en rojo
                QTextCursor c( bloque );
                c.select( QTextCursor::LineUnderCursor );
                QTextCharFormat fmt;
                fmt.setBackground( QColor( 80, 20, 20 ) );
                c.setCharFormat( fmt );
            }
            else  {
                lEstado->setStyleSheet( "color: #6f6;" );
                lEstado->setText( "Sin errores." );
                // Limpiar resaltado de la línea
                QTextCursor c( bloque );
                c.select( QTextCursor::LineUnderCursor );
                QTextCharFormat fmt;
                fmt.setBackground( QColor( 30, 30, 30 ) );
                c.setCharFormat( fmt );
            }
        }
        lineaPrevia = lineaActual;
    }
}

void EditorPrincipal::slot_exportarJpg()  {
    // Renderiza todo el contenido del editor a una imagen JPG legible.
    QString texto = editor->toPlainText();
    QStringList lineas = texto.split( '\n' );

    QFont fuente( "Consolas", 12 );
    QFontMetrics fm( fuente );
    int alturaLinea = fm.height();
    int ancho = 800;
    int alto = qMax( 200, alturaLinea * ( lineas.size() + 2 ) );

    QImage img( ancho, alto, QImage::Format_RGB32 );
    img.fill( Qt::white );

    QPainter p( &img );
    p.setFont( fuente );
    p.setPen( Qt::black );

    int y = alturaLinea;
    for ( const QString & linea : lineas )  {
        p.drawText( 20, y, linea );
        y += alturaLinea;
    }
    p.end();

    QString ruta = QFileDialog::getSaveFileName(
        this, "Exportar a JPG", rutaExportacion, "Imágenes (*.jpg)"
    );
    if ( ruta.isEmpty() )  return;

    if ( img.save( ruta, "JPG", 92 ) )  {
        QMessageBox::information( this, "Exportado", "Código guardado en:\n" + ruta );
        registrarEvento( "Código exportado a " + ruta );
    }
    else  {
        QMessageBox::warning( this, "Error", "No se pudo guardar la imagen." );
        registrarEvento( "Falló la exportación a " + ruta );
    }
}

void EditorPrincipal::validarLineaActual()  {
    if ( ! validador )  return;
    QTextBlock bloque = editor->textCursor().block();
    QString linea = bloque.text();
    bool ok = validador->validarLinea( linea );
    if ( ! ok )  {
        lEstado->setStyleSheet( "color: #f66;" );
        lEstado->setText(
            QString( "Línea actual: %1" ).arg( validador->mensajeError() )
        );
    }
    else  {
        lEstado->setStyleSheet( "color: #6f6;" );
        lEstado->setText( "Sin errores." );
    }
}

// ----------- Eventos redefinidos -----------

void EditorPrincipal::closeEvent( QCloseEvent * event )  {
    auto resp = QMessageBox::question(
        this, "Confirmar salida",
        "¿Salir del editor? Se perderá el contenido no exportado.",
        QMessageBox::Yes | QMessageBox::No
    );
    if ( resp == QMessageBox::Yes )  {
        registrarEvento( "Editor cerrado por usuario" );
        event->accept();
    }
    else  {
        event->ignore();
    }
}

void EditorPrincipal::keyPressEvent( QKeyEvent * event )  {
    // Atajos del editor: Ctrl+S exporta, Esc desfocea
    if ( event->modifiers() & Qt::ControlModifier && event->key() == Qt::Key_S )  {
        slot_exportarJpg();
        return;
    }
    Pantalla::keyPressEvent( event );
}

void EditorPrincipal::mousePressEvent( QMouseEvent * event )  {
    registrarEvento( QString( "Click en (%1, %2)" )
                         .arg( event->pos().x() )
                         .arg( event->pos().y() ) );
    Pantalla::mousePressEvent( event );
}

void EditorPrincipal::resizeEvent( QResizeEvent * event )  {
    Pantalla::resizeEvent( event );
    // Adapta el ancho del panel CV: si la ventana es muy chica, lo oculta
    // (mantenemos simple acá: el QHBoxLayout ya se encarga del resto).
}

void EditorPrincipal::focusInEvent( QFocusEvent * event )  {
    registrarEvento( "Editor recibió foco" );
    Pantalla::focusInEvent( event );
}

void EditorPrincipal::focusOutEvent( QFocusEvent * event )  {
    registrarEvento( "Editor perdió foco => validando estado" );
    validarEstado();
    Pantalla::focusOutEvent( event );
}

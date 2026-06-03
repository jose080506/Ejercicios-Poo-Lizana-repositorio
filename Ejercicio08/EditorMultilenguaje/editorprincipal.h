#ifndef EDITORPRINCIPAL_H
#define EDITORPRINCIPAL_H

#include "pantalla.h"

class QPlainTextEdit;
class QComboBox;
class QPushButton;
class QLabel;
class ValidadorSintaxis;

class EditorPrincipal : public Pantalla  {
    Q_OBJECT

public:
    EditorPrincipal( QWidget * parent = nullptr );
    ~EditorPrincipal();

    void inicializarUI() override;
    void conectarEventos() override;
    void cargarDatos() override;
    void validarEstado() override;
    void registrarEvento( const QString & descripcion ) override;

protected:
    // Eventos redefinidos
    void closeEvent( QCloseEvent * event ) override;
    void keyPressEvent( QKeyEvent * event ) override;
    void mousePressEvent( QMouseEvent * event ) override;
    void resizeEvent( QResizeEvent * event ) override;
    void focusInEvent( QFocusEvent * event ) override;
    void focusOutEvent( QFocusEvent * event ) override;

private slots:
    void slot_cambiarLenguaje( int indice );
    void slot_lineaCambiada();
    void slot_exportarJpg();

private:
    void validarLineaActual();
    void armarPanelCV( QWidget * contenedor );

    QPlainTextEdit * editor;
    QComboBox * cbLenguaje;
    QPushButton * pbExportar;
    QLabel * lEstado;
    QLabel * lLenguaje;

    ValidadorSintaxis * validador;     // puntero a clase base (polimorfismo)
    int lineaPrevia;
    QString rutaExportacion;
};

#endif // EDITORPRINCIPAL_H

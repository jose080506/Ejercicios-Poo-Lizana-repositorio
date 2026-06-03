#ifndef EDITORNOTAS_H
#define EDITORNOTAS_H

#include <QDialog>

class QPlainTextEdit;
class QLabel;

// EditorNotas: diálogo para editar las notas de un TP.
// Guardado manual con botón "Guardar" (la consigna lo pide así).

class EditorNotas : public QDialog  {
    Q_OBJECT

public:
    EditorNotas( const QString & tituloTP, const QString & notasIniciales,
                 QWidget * parent = nullptr );

    QString notas() const;
    bool fueGuardado() const  {  return guardado;  }

private slots:
    void slot_guardar();
    void slot_textoCambiado();

private:
    QPlainTextEdit * editor;
    QLabel         * lEstado;
    QString          notasGuardadas;
    bool             guardado;
    bool             hayCambiosSinGuardar;
};

#endif // EDITORNOTAS_H

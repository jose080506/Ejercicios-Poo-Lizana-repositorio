#ifndef DIALOGOTP_H
#define DIALOGOTP_H

#include <QDialog>
#include "tp.h"

class QLineEdit;
class QDateEdit;
class QComboBox;

// DialogoTP: ventana modal para alta y edición de un TP.
// Construido por código (sin .ui) para variar respecto del Login.

class DialogoTP : public QDialog  {
    Q_OBJECT

public:
    // Para alta: tp puede ser un TP vacío. Para edición: pasar el TP cargado.
    DialogoTP( const TP & tp, QWidget * parent = nullptr );

    TP obtenerTP() const;

private:
    QLineEdit * leTitulo;
    QLineEdit * leMateria;
    QDateEdit * deFecha;
    QComboBox * cbPrioridad;
    QComboBox * cbEstado;

    int idActual;
    QString notasActuales;
};

#endif // DIALOGOTP_H

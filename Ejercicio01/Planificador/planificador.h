#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H

#include <QWidget>
#include <QList>
#include "tp.h"

class QGridLayout;
class QComboBox;
class QLineEdit;
class QPlainTextEdit;
class QPushButton;
class QScrollArea;
class QLabel;
class AdminArchivos;

// Planificador: ventana principal con el tablero de TPs.
// Hereda QWidget (no QMainWindow) como pide la consigna.

class Planificador : public QWidget  {
    Q_OBJECT

public:
    Planificador( AdminArchivos * admin, const QString & usuario,
                  QWidget * parent = nullptr );

private slots:
    void slot_nuevoTP();
    void slot_editarTP( int id );
    void slot_notasTP( int id );
    void slot_eliminarTP( int id );
    void slot_recargar();
    void slot_filtroCambiado();
    void slot_logout();

private:
    void armarUI();
    void recargarTablero();
    bool pasaFiltros( const TP & tp ) const;
    void refrescarHistorial();

    // Datos
    AdminArchivos *  admin;
    QString          usuario;
    QList< TP >      tps;

    // UI - filtros
    QComboBox      * cbFiltroEstado;
    QComboBox      * cbFiltroPrioridad;
    QLineEdit      * leBuscar;

    // UI - grilla del tablero
    QWidget        * contenedorGrilla;
    QGridLayout    * grilla;
    QScrollArea    * scroll;

    // UI - historial
    QPlainTextEdit * pteHistorial;

    // UI - cabecera
    QLabel         * lBienvenida;
};

#endif // PLANIFICADOR_H

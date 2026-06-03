#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QColor>

class Pintura;
class AdminDB;
class QLabel;

// MainWindow: contiene el Pintura y muestra el estado actual
// (color y grosor) abajo. Persiste cada punto en la base via AdminDB.

class MainWindow : public QWidget  {
    Q_OBJECT

public:
    MainWindow( AdminDB * adminDB, const QString & usuario,
                QWidget * parent = nullptr );

private slots:
    void slot_puntoDibujado( int x, int y, const QColor & color,
                             int grosor, bool esInicio );
    void slot_estadoCambiado( const QColor & color, int grosor );
    void slot_lienzoBorrado();
    void slot_trazoDeshecho();

private:
    void actualizarEstado( const QColor & color, int grosor );

    Pintura * pintura;
    AdminDB * adminDB;        // no owner
    QLabel  * lEstado;

    qint64    sesion;          // id único de esta sesión
    int       trazoActual;     // contador local de trazos en esta sesión
    int       ordenActual;     // contador de puntos dentro del trazo
    QString   usuario;
};

#endif // MAINWINDOW_H

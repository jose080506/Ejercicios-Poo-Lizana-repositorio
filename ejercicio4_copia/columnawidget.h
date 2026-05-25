#ifndef COLUMNAWIDGET_H
#define COLUMNAWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include "tarjetawidget.h"

class ColumnaWidget : public QWidget {
    Q_OBJECT

public:
    explicit ColumnaWidget(int id, const QString &nombre, QWidget *parent = nullptr);

    int     getId()     const { return id; }
    QString getNombre() const { return nombre; }

    void agregarTarjeta(int tarjetaId, const QString &titulo,
                        const QString &descripcion);
    void limpiarTarjetas();

signals:
    void signal_nuevaTarjeta(int columnaId);
    void signal_eliminarColumna(int columnaId);
    void signal_editarTarjeta(int tarjetaId, const QString &titulo,
                               const QString &descripcion);
    void signal_eliminarTarjeta(int tarjetaId);
    void signal_moverTarjetaIzquierda(int tarjetaId, int columnaId);
    void signal_moverTarjetaDerecha(int tarjetaId, int columnaId);

private slots:
    void slot_nuevaTarjeta();
    void slot_eliminarColumna();
    void slot_editarTarjeta(int id, const QString &titulo,
                             const QString &descripcion);
    void slot_eliminarTarjeta(int id);
    void slot_moverIzquierda(int tarjetaId);
    void slot_moverDerecha(int tarjetaId);

private:
    int      id;
    QString  nombre;
    QWidget     *contenedorTarjetas;
    QVBoxLayout *layoutTarjetas;
};

#endif // COLUMNAWIDGET_H

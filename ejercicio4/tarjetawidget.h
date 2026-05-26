#ifndef TARJETAWIDGET_H
#define TARJETAWIDGET_H

#include <QWidget>

class TarjetaWidget : public QWidget {
    Q_OBJECT

public:
    explicit TarjetaWidget(int id, const QString &titulo,
                           const QString &descripcion,
                           QWidget *parent = nullptr);
    int getId() const { return id; }

signals:
    void signal_editar(int id, const QString &titulo, const QString &descripcion);
    void signal_eliminar(int id);
    void signal_moverIzquierda(int id);
    void signal_moverDerecha(int id);
    void signal_subir(int id);    // reordenar dentro de la columna
    void signal_bajar(int id);    // reordenar dentro de la columna

private slots:
    void slot_editar();
    void slot_eliminar();
    void slot_moverIzquierda();
    void slot_moverDerecha();
    void slot_subir();
    void slot_bajar();

private:
    int     id;
    QString titulo;
    QString descripcion;
};

#endif // TARJETAWIDGET_H

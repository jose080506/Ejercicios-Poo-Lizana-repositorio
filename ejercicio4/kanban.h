#ifndef KANBAN_H
#define KANBAN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTimer>
#include <QList>
#include "apiclient.h"
#include "columnawidget.h"

class KanbanWidget : public QWidget {
    Q_OBJECT

public:
    explicit KanbanWidget(QWidget *parent = nullptr);

private slots:
    void slot_actualizarTablero();
    void slot_tableroRecibido(const QByteArray &datos);
    void slot_operacionCompletada();
    void slot_errorOcurrido(const QString &mensaje);

    void slot_nuevaColumna();
    void slot_eliminarColumna(int columnaId);
    void slot_nuevaTarjeta(int columnaId);
    void slot_editarTarjeta(int tarjetaId, const QString &titulo,
                             const QString &descripcion);
    void slot_eliminarTarjeta(int tarjetaId);
    void slot_moverTarjetaIzquierda(int tarjetaId, int columnaActualId);
    void slot_moverTarjetaDerecha(int tarjetaId, int columnaActualId);
    void slot_reordenarTarjetas(int columnaId, QList<int> orden);

private:
    ApiClient   *apiClient;
    QHBoxLayout *layoutColumnas;
    QTimer      *timerPolling;

    QList<ColumnaWidget*> columnas;
    QList<int>            idsColumnas;

    void limpiarColumnas();
    void conectarColumna(ColumnaWidget *col);
    int  columnaVecina(int columnaActualId, int delta);
};

#endif // KANBAN_H

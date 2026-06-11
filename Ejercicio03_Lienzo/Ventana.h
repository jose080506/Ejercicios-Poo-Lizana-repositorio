#ifndef VENTANA_H
#define VENTANA_H

#include "Lienzo.h"
#include "ModeloDibujo.h"
#include "Sincronizador.h"

#include <QLabel>
#include <QMainWindow>

class Ventana : public QMainWindow {
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = nullptr);

private slots:
    void slot_guardar();
    void slot_alGuardarOk();
    void slot_alGuardarError(const QString &detalle);
    void slot_alRecuperar(const QJsonArray &trazos);
    void slot_alRecuperarError(const QString &detalle);

private:
    void armarToolbar();
    void mostrarEstado(const QString &texto, const QString &color = "#ffffff");

    ModeloDibujo  *m_modelo;
    Lienzo        *m_lienzo;
    Sincronizador *m_sinc;
    QLabel        *m_lblEstado;
};

#endif // VENTANA_H

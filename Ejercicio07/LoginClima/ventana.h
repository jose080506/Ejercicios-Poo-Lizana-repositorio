#ifndef VENTANA_H
#define VENTANA_H

#include "pantalla.h"

class QLabel;
class QNetworkAccessManager;
class QNetworkReply;
class QPixmap;

// Ventana principal. Full screen. Espera a que la imagen de fondo
// termine de descargarse antes de mostrarse.

class Ventana : public Pantalla  {
    Q_OBJECT

public:
    Ventana( QWidget * parent = nullptr );
    ~Ventana();

    void mostrar() override;
    void cerrar() override;

protected:
    void resizeEvent( QResizeEvent * event ) override;   // para reescalar fondo

private slots:
    void slot_imagenDescargada( QNetworkReply * reply );

private:
    void armarUI();
    void aplicarFondo();

    QLabel * lFondo;          // fondo escalado
    QLabel * lFoto;           // foto del CV
    QLabel * lDescripcion;    // texto del CV (LinkedIn-style)
    QPixmap * pixmapFondo;    // imagen original sin escalar

    QNetworkAccessManager * manager;
};

#endif // VENTANA_H

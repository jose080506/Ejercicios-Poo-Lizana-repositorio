#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QLabel;

class Login : public QWidget  {
    Q_OBJECT

public:
    Login( QWidget * parent = nullptr );

private slots:
    void slot_validar();

private:
    QLineEdit * usuario;
    QLineEdit * clave;
    QPushButton * boton_ingresar;
    QLabel * mensaje;
};

#endif // LOGIN_H

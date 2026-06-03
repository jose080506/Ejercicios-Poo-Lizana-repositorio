#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui  {
    class Login;
}

class AdminArchivos;

class Login : public QWidget  {
    Q_OBJECT

public:
    Login( AdminArchivos * admin, QWidget * parent = nullptr );
    ~Login();

signals:
    void loginExitoso( const QString & usuario );

private slots:
    void slot_validar();

private:
    Ui::Login * ui;
    AdminArchivos * admin;
};

#endif // LOGIN_H

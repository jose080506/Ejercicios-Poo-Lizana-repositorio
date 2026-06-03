#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui  {
    class Login;
}

class AdminDB;

class Login : public QWidget  {
    Q_OBJECT

public:
    Login( AdminDB * adminDB, QWidget * parent = nullptr );
    ~Login();

signals:
    void loginExitoso( const QString & usuario );

private slots:
    void slot_validar();

private:
    Ui::Login * ui;
    AdminDB * adminDB;     // no owner, viene de afuera
};

#endif // LOGIN_H

/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QGridLayout *gridLayout;
    QLabel *lTitulo;
    QLabel *lUsuario;
    QLineEdit *leUsuario;
    QLabel *lClaveTexto;
    QLineEdit *leClave;
    QPushButton *pbIngresar;
    QLabel *lMensaje;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(360, 220);
        gridLayout = new QGridLayout(Login);
        gridLayout->setObjectName("gridLayout");
        lTitulo = new QLabel(Login);
        lTitulo->setObjectName("lTitulo");
        lTitulo->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lTitulo, 0, 0, 1, 2);

        lUsuario = new QLabel(Login);
        lUsuario->setObjectName("lUsuario");

        gridLayout->addWidget(lUsuario, 1, 0, 1, 1);

        leUsuario = new QLineEdit(Login);
        leUsuario->setObjectName("leUsuario");

        gridLayout->addWidget(leUsuario, 1, 1, 1, 1);

        lClaveTexto = new QLabel(Login);
        lClaveTexto->setObjectName("lClaveTexto");

        gridLayout->addWidget(lClaveTexto, 2, 0, 1, 1);

        leClave = new QLineEdit(Login);
        leClave->setObjectName("leClave");
        leClave->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(leClave, 2, 1, 1, 1);

        pbIngresar = new QPushButton(Login);
        pbIngresar->setObjectName("pbIngresar");

        gridLayout->addWidget(pbIngresar, 3, 0, 1, 2);

        lMensaje = new QLabel(Login);
        lMensaje->setObjectName("lMensaje");
        lMensaje->setStyleSheet(QString::fromUtf8("color: rgb(200, 30, 30);"));
        lMensaje->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lMensaje, 4, 0, 1, 2);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Editor multilenguaje - Login", nullptr));
        lTitulo->setText(QCoreApplication::translate("Login", "<h2>Iniciar sesi\303\263n</h2>", nullptr));
        lUsuario->setText(QCoreApplication::translate("Login", "Usuario:", nullptr));
        lClaveTexto->setText(QCoreApplication::translate("Login", "Clave:", nullptr));
        pbIngresar->setText(QCoreApplication::translate("Login", "Ingresar", nullptr));
        lMensaje->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H

#ifndef VALIDADORPYTHON_H
#define VALIDADORPYTHON_H

#include "validadorsintaxis.h"

class ValidadorPython : public ValidadorSintaxis  {
    Q_OBJECT

public:
    ValidadorPython( QObject * parent = nullptr );

    bool validarLinea( const QString & linea ) override;
    QString mensajeError() const override;
    QString nombreLenguaje() const override;

private:
    QString ultimoError;
};

#endif // VALIDADORPYTHON_H

#ifndef VALIDADORCPP_H
#define VALIDADORCPP_H

#include "validadorsintaxis.h"

class ValidadorCpp : public ValidadorSintaxis  {
    Q_OBJECT

public:
    ValidadorCpp( QObject * parent = nullptr );

    bool validarLinea( const QString & linea ) override;
    QString mensajeError() const override;
    QString nombreLenguaje() const override;

private:
    QString ultimoError;
};

#endif // VALIDADORCPP_H

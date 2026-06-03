#ifndef VALIDADORJAVA_H
#define VALIDADORJAVA_H

#include "validadorsintaxis.h"

class ValidadorJava : public ValidadorSintaxis  {
    Q_OBJECT

public:
    ValidadorJava( QObject * parent = nullptr );

    bool validarLinea( const QString & linea ) override;
    QString mensajeError() const override;
    QString nombreLenguaje() const override;

private:
    QString ultimoError;
};

#endif // VALIDADORJAVA_H

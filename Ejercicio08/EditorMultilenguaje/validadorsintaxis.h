#ifndef VALIDADORSINTAXIS_H
#define VALIDADORSINTAXIS_H

#include <QObject>
#include <QString>

// Clase abstracta para validación de sintaxis por lenguaje.
// El editor trabaja contra un puntero a ValidadorSintaxis, sin saber
// si por debajo es Cpp, Python o Java.

class ValidadorSintaxis : public QObject  {
    Q_OBJECT

public:
    ValidadorSintaxis( QObject * parent = nullptr );
    virtual ~ValidadorSintaxis();

    // Valida una línea individual. Devuelve true si es válida.
    virtual bool validarLinea( const QString & linea ) = 0;

    // Devuelve el último mensaje de error en formato amigable.
    virtual QString mensajeError() const = 0;

    // Nombre del lenguaje (para mostrar en la UI / log)
    virtual QString nombreLenguaje() const = 0;

protected:
    // Helper común para chequear balance de paréntesis, llaves y corchetes.
    // Util a todas las derivadas, así no se repite código.
    bool balanceadoBasico( const QString & linea, QString & motivo ) const;
};

#endif // VALIDADORSINTAXIS_H

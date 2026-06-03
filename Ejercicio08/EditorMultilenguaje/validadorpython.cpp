#include "validadorpython.h"

ValidadorPython::ValidadorPython( QObject * parent ) : ValidadorSintaxis( parent )  {
}

bool ValidadorPython::validarLinea( const QString & linea )  {
    ultimoError.clear();

    QString limpia = linea.trimmed();

    if ( limpia.isEmpty() )           return true;
    if ( limpia.startsWith( "#" ) )   return true;   // comentario

    // Balance básico
    QString motivo;
    if ( ! balanceadoBasico( limpia, motivo ) )  {
        ultimoError = motivo;
        return false;
    }

    // Las estructuras de control deben terminar con ":"
    QStringList controles = { "def ", "class ", "if ", "elif ", "else",
                              "for ", "while ", "try", "except", "finally",
                              "with " };
    for ( const QString & c : controles )  {
        if ( limpia.startsWith( c ) )  {
            if ( ! limpia.endsWith( ":" ) )  {
                ultimoError = "Falta ':' al final de la estructura de control";
                return false;
            }
            break;
        }
    }

    // En Python NO debería terminar con ";"
    if ( limpia.endsWith( ";" ) )  {
        ultimoError = "Python no usa ';' al final de la línea";
        return false;
    }

    return true;
}

QString ValidadorPython::mensajeError() const  {
    return ultimoError;
}

QString ValidadorPython::nombreLenguaje() const  {
    return "Python";
}

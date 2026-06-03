#include "validadorjava.h"

ValidadorJava::ValidadorJava( QObject * parent ) : ValidadorSintaxis( parent )  {
}

bool ValidadorJava::validarLinea( const QString & linea )  {
    ultimoError.clear();

    QString limpia = linea.trimmed();

    if ( limpia.isEmpty() )            return true;
    if ( limpia.startsWith( "//" ) )   return true;
    if ( limpia.startsWith( "/*" ) )   return true;
    if ( limpia.startsWith( "*" ) )    return true;
    if ( limpia.startsWith( "import " ) || limpia.startsWith( "package " ) )  {
        if ( ! limpia.endsWith( ";" ) )  {
            ultimoError = "import/package debe terminar con ';'";
            return false;
        }
        return true;
    }

    QString motivo;
    if ( ! balanceadoBasico( limpia, motivo ) )  {
        ultimoError = motivo;
        return false;
    }

    // En Java cada statement termina en ;
    QChar ult = limpia[ limpia.size() - 1 ];
    if ( ult != '{' && ult != '}' && ult != ';' && ult != ',' )  {
        bool esControl = limpia.startsWith( "if " )    || limpia.startsWith( "if(" )    ||
                         limpia.startsWith( "for " )   || limpia.startsWith( "for(" )   ||
                         limpia.startsWith( "while " ) || limpia.startsWith( "while(" ) ||
                         limpia.startsWith( "else" )   || limpia.startsWith( "do" )     ||
                         limpia.startsWith( "switch" ) || limpia.startsWith( "case" )   ||
                         limpia.startsWith( "class " ) || limpia.startsWith( "public " ) ||
                         limpia.startsWith( "private " ) || limpia.startsWith( "protected " );
        if ( ! esControl )  {
            ultimoError = "Probablemente falte ';' al final";
            return false;
        }
    }

    return true;
}

QString ValidadorJava::mensajeError() const  {
    return ultimoError;
}

QString ValidadorJava::nombreLenguaje() const  {
    return "Java";
}

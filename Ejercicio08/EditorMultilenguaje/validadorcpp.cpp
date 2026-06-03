#include "validadorcpp.h"

ValidadorCpp::ValidadorCpp( QObject * parent ) : ValidadorSintaxis( parent )  {
}

bool ValidadorCpp::validarLinea( const QString & linea )  {
    ultimoError.clear();

    QString limpia = linea.trimmed();

    // Líneas vacías o comentarios => válidas
    if ( limpia.isEmpty() )            return true;
    if ( limpia.startsWith( "//" ) )   return true;
    if ( limpia.startsWith( "/*" ) )   return true;
    if ( limpia.startsWith( "*" ) )    return true;
    if ( limpia.startsWith( "#" ) )    return true;   // directiva de preprocesador

    // Chequeo de balance básico
    QString motivo;
    if ( ! balanceadoBasico( limpia, motivo ) )  {
        ultimoError = motivo;
        return false;
    }

    // Si NO termina en {, }, ;, : ni , y no es palabra de control => probablemente falta ;
    QChar ult = limpia[ limpia.size() - 1 ];
    if ( ult != '{' && ult != '}' && ult != ';' && ult != ':' && ult != ',' && ult != '\\' )  {
        // Permitir control flow sin punto y coma
        bool esControl = limpia.startsWith( "if " )    || limpia.startsWith( "if(" )    ||
                         limpia.startsWith( "for " )   || limpia.startsWith( "for(" )   ||
                         limpia.startsWith( "while " ) || limpia.startsWith( "while(" ) ||
                         limpia.startsWith( "else" )   || limpia.startsWith( "do" )     ||
                         limpia.startsWith( "switch" ) || limpia.startsWith( "case" )   ||
                         limpia.startsWith( "class " ) || limpia.startsWith( "struct " );
        if ( ! esControl )  {
            ultimoError = "Probablemente falte ';' al final";
            return false;
        }
    }

    return true;
}

QString ValidadorCpp::mensajeError() const  {
    return ultimoError;
}

QString ValidadorCpp::nombreLenguaje() const  {
    return "C++";
}

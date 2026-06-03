#include "validadorsintaxis.h"

ValidadorSintaxis::ValidadorSintaxis( QObject * parent ) : QObject( parent )  {
}

ValidadorSintaxis::~ValidadorSintaxis()  {
}

bool ValidadorSintaxis::balanceadoBasico( const QString & linea, QString & motivo ) const  {
    int parens = 0, braces = 0, brackets = 0;
    bool dentroString = false;
    QChar comillaActiva;

    for ( int i = 0; i < linea.size(); ++i )  {
        QChar c = linea[ i ];

        // Manejo simple de strings (no soporta escapes complejos)
        if ( dentroString )  {
            if ( c == comillaActiva )  dentroString = false;
            continue;
        }
        if ( c == '"' || c == '\'' )  {
            dentroString = true;
            comillaActiva = c;
            continue;
        }

        if ( c == '(' )  ++parens;
        else if ( c == ')' )  --parens;
        else if ( c == '{' )  ++braces;
        else if ( c == '}' )  --braces;
        else if ( c == '[' )  ++brackets;
        else if ( c == ']' )  --brackets;

        if ( parens   < 0 )  {  motivo = "Cierre de paréntesis sin apertura";  return false;  }
        if ( braces   < 0 )  {  motivo = "Cierre de llave sin apertura";       return false;  }
        if ( brackets < 0 )  {  motivo = "Cierre de corchete sin apertura";    return false;  }
    }

    if ( dentroString )  {  motivo = "String sin cerrar";                  return false;  }
    if ( parens   != 0 )  {  motivo = "Paréntesis sin balancear en la línea"; return false;  }
    if ( brackets != 0 )  {  motivo = "Corchetes sin balancear en la línea"; return false;  }
    // Las llaves pueden quedar abiertas (multi-línea), no las chequeamos por línea.

    return true;
}

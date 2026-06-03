#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include "admindb.h"
#include "login.h"
#include "mainwindow.h"

// Función helper: conecta la señal de login con la apertura de la ventana
// principal. Se hace con una lambda para mantener el main.cpp simple.

int main( int argc, char ** argv )  {
    QApplication app( argc, argv );

    // Archivo SQLite al lado del ejecutable
    QString archivoSqlite = "pintura.db";

    AdminDB adminDB;
    if ( ! adminDB.conectar( archivoSqlite ) )  {
        QMessageBox::critical( nullptr, "Error",
            QString( "No se pudo abrir la base de datos:\n%1\n\n"
                     "Crear el archivo ejecutando crear_base.sql con SQLiteStudio "
                     "o sqlite3, y dejarlo al lado del .exe." )
                .arg( archivoSqlite ) );
        return 1;
    }

    Login login( &adminDB );
    login.show();

    MainWindow * ventana = nullptr;

    QObject::connect( &login, &Login::loginExitoso,
                      [ &login, &ventana, &adminDB ]( const QString & usuario )  {
        ventana = new MainWindow( &adminDB, usuario );
        ventana->setAttribute( Qt::WA_DeleteOnClose );
        ventana->show();
        login.close();
    } );

    return app.exec();
}

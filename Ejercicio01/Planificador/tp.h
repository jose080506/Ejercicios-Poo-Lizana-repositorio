#ifndef TP_H
#define TP_H

#include <QString>
#include <QDate>

// Estructura simple para un Trabajo Práctico.
// Estados:     "Pendiente" | "En curso" | "Entregado"
// Prioridades: "Alta" | "Media" | "Baja"

struct TP  {
    int     id;
    QString titulo;
    QString materia;
    QDate   fechaEntrega;
    QString prioridad;
    QString estado;
    QString notas;
};

#endif // TP_H

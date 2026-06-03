# Ejercicio 01 - Planificador de Trabajos Prácticos

App Qt para administrar TPs con login, filtros, edición, notas y persistencia local.

## Arquitectura de clases

```
main.cpp
  → AdminArchivos: maneja toda la persistencia
  → Login (con .ui): valida contra users.csv
  → Planificador (QWidget, ventana principal): grilla de TPs + filtros + historial
       ↓
       DialogoTP (QDialog): alta/edición de un TP
       EditorNotas (QDialog): edición de notas con guardado manual

TP (struct): datos de un trabajo práctico
```

## Cumplimiento del checklist

| Item de la consigna | Estado |
|---------------------|--------|
| Login con validación contra archivo | ✅ users.csv |
| Sesión persistente 5 min | ✅ sesion.dat con timestamp |
| Ventana principal con QGridLayout | ✅ filas con QLabel + botones |
| Filtros por estado y prioridad | ✅ 2 QComboBox + búsqueda libre |
| Alta/edición/eliminación | ✅ DialogoTP |
| Editor de notas con guardado manual | ✅ EditorNotas |
| Historial en UI y en archivo | ✅ historial.log + QPlainTextEdit |
| No usar QML | ✅ |
| Usar QWidget (no QMainWindow) | ✅ |
| Código en clases | ✅ 6 clases en archivos separados |

## Archivos generados al correr

| Archivo          | Para qué |
|------------------|----------|
| `users.csv`      | Usuarios y claves (texto plano) |
| `tps.csv`        | Trabajos prácticos (separador `\|`) |
| `sesion.dat`     | usuario + timestamp (5 min de vida) |
| `historial.log`  | Log con fecha y acción |

⚠️ **Importante**: estos archivos se crean **al lado del `.exe`**, no en la carpeta de fuentes.
Si los modificás a mano (por ejemplo agregar un usuario), editá la copia que está en la carpeta `debug` del build.

## Usuarios por defecto

Cuando la app no encuentra `users.csv`, lo crea con estos dos usuarios:

- `admin` / `1234`
- `jose` / `qwerty`

## Cómo se persisten los TPs

CSV con separador `|` (para que los títulos puedan tener comas):

```
id|titulo|materia|fecha|prioridad|estado|notas
1|TP1 Login|POO|2026-06-15|Alta|En curso|Notas multilínea con \n
2|TP2 Dibujo|POO|2026-06-22|Media|Pendiente|
```

Los saltos de línea de las notas se escapan como `\n` para mantener una fila por TP.

## Sesión de 5 minutos

Cuando hacés login exitoso, `AdminArchivos::guardarSesion()` escribe:
```
admin
1717452345123
```
(usuario + timestamp Unix ms)

En el próximo arranque, `sesionActiva()` chequea si pasaron menos de 5 minutos:
- Si sí → te salta el login y va directo al tablero
- Si no → muestra el login normalmente

El botón "Cerrar sesión" borra `sesion.dat`.

## Filtros del tablero

Tres filtros combinables:

1. **Estado** (combo): Todos / Pendiente / En curso / Entregado
2. **Prioridad** (combo): Todas / Alta / Media / Baja
3. **Búsqueda libre**: por título o materia, case-insensitive

Cada vez que cambia un filtro, se redibuja la grilla.

## Colores por prioridad

Las filas se pintan según prioridad para localizar rápido lo urgente:

- 🔴 Alta → rojo claro
- 🟡 Media → amarillo claro
- 🟢 Baja → verde claro

## Historial

Cada acción importante (login, alta, edición, eliminación, guardar notas, cerrar sesión) queda registrada en `historial.log` y se muestra en el panel inferior del tablero.

Formato del log:
```
[2026-06-03 18:42:11] jose => Login OK
[2026-06-03 18:42:34] jose => Crea TP: TP1 Login
[2026-06-03 18:42:51] jose => Edita TP: TP1 Login
[2026-06-03 18:43:02] jose => Guarda notas de: TP1 Login
```

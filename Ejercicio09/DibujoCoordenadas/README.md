# Ejercicio 09 - Coordenadas en base de datos

## Arquitectura

```
main.cpp
  → AdminDB.conectar("pintura.db")
  → Login (con .ui, valida contra tabla usuarios)
  → MainWindow (contiene Pintura)

AdminDB (QObject)
  - conectar al SQLite
  - validarUsuario(u, c)
  - registrarLog(tipo, usuario)   ← nunca guarda la clave
  - guardarPunto(sesion, trazo, orden, x, y, color, grosor, esInicio)

Login (QWidget + .ui)
  - emite loginExitoso(usuario) cuando la validación contra DB es OK

Pintura (QWidget)
  - lienzo QPixmap + paintEvent
  - mouse: dibuja a mano alzada
  - rueda: ajusta grosor
  - R/G/B: cambia color
  - Escape: borra todo
  - Ctrl+Z: deshace último trazo (cap 10)
  - emite puntoDibujado(x, y, color, grosor, esInicio) por cada punto

MainWindow (QWidget)
  - contiene Pintura
  - conecta sus signals a AdminDB para persistir cada punto
  - muestra barra de estado: usuario, color, grosor
```

## Estructura de la base SQLite (`pintura.db`)

```sql
usuarios (id, usuario, clave, nombre, apellido)
logs     (id, fecha, tipo, usuario)                -- nunca guarda clave
trazos   (id, sesion, trazo, orden, x, y, color, grosor, es_inicio)
```

- **`sesion`**: timestamp Unix del momento en que se abrió la ventana.
- **`trazo`**: nro de trazo dentro de la sesión (cada vez que apretás y soltás el botón es un trazo).
- **`orden`**: posición del punto dentro del trazo.
- **`es_inicio`**: 1 si es el primer punto del trazo, 0 si es continuación. Sirve para reconstruir: si es_inicio = 1 hacés `drawPoint`, si no hacés `drawLine` desde el anterior.

## Cómo correrlo

1. Descomprimí el zip
2. Abrí `DibujoCoordenadas.pro` con Qt Creator
3. **Copiá `pintura.db` a la carpeta del `.exe`** (carpeta `debug` dentro del build), igual que el `config.ini` de los ejercicios anteriores
4. Compilá y corré
5. Login: `admin` / `1234` o `jose` / `qwerty`

## Si querés crear la base de cero

Con SQLiteStudio:
1. *Database → Add Database → Create new database*
2. Nombre: `pintura.db`
3. Abrir el SQL Editor (Alt+E)
4. Pegar el contenido de `crear_base.sql`
5. Ejecutar (F9)

O por terminal:
```
sqlite3 pintura.db < crear_base.sql
```

## Controles del lienzo

| Acción            | Atajo            |
|-------------------|------------------|
| Dibujar           | Click izquierdo + arrastrar |
| Cambiar grosor    | Rueda del mouse (+1 / -1) |
| Color rojo        | R                |
| Color verde       | G                |
| Color azul        | B                |
| Borrar lienzo     | Escape           |
| Deshacer trazo    | Ctrl + Z (hasta 10) |

## Reconstruir un dibujo desde la base

Para verificar que la persistencia funciona, abrí `pintura.db` con SQLiteStudio
y mirá la tabla `trazos`. Cada fila es un punto, ordenado por sesión, trazo y
orden. Recorriendo en ese orden y aplicando `drawPoint` cuando `es_inicio=1` o
`drawLine` cuando es continuación, se reconstruye el dibujo exacto.

Una query útil para ver el dibujo de la última sesión:
```sql
SELECT trazo, orden, x, y, color, grosor, es_inicio
FROM trazos
WHERE sesion = (SELECT MAX(sesion) FROM trazos)
ORDER BY trazo, orden;
```

## Logs

Los accesos y los intentos fallidos quedan en la tabla `logs`. Para verlos:
```sql
SELECT fecha, tipo, usuario FROM logs ORDER BY fecha DESC;
```

⚠️ **Nunca** se guarda la clave en los logs (la consigna lo pide explícitamente).
Solo se guarda el usuario que intentó ingresar.

## Notas técnicas

- La pintura se hace sobre un `QPixmap` que actúa como **doble buffer**. El `paintEvent` solo blitea esa pixmap. Así no se pierde el dibujo si la ventana se redimensiona o se tapa con otra ventana.
- Cada punto se persiste en la base **en tiempo real** mientras se dibuja. Esto es rendimientemente costoso para dibujos largos pero cumple la consigna de "poder reconstruir el trazo".
- El undo (Ctrl+Z) elimina el último trazo de la pila local y redibuja todo. **No borra los puntos de la base** — se mantiene historial completo.

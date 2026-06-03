# Ejercicio 08 - Editor multilenguaje

## Arquitectura de clases

```
Pantalla (abstracta, hereda QWidget)
  ├── Login            (.ui de QtDesigner, admin:1234, bloqueo 3 intentos)
  ├── EditorPrincipal  (full screen, editor + panel CV + export JPG)
  └── ModoBloqueado    (cuenta regresiva, no se puede cerrar)

ValidadorSintaxis (abstracta, hereda QObject)
  ├── ValidadorCpp     (balance + ';' al final + control flow)
  ├── ValidadorPython  (':' en estructuras, NO ';', balance)
  └── ValidadorJava    (import/package con ';', balance, ';' al final)

Controlador (QObject)
  - Trabaja contra punteros a Pantalla * (polimorfismo)
  - Switchea entre Login → Editor / Login → Bloqueado → Login
```

## Funciones virtuales puras (5)

En `Pantalla`:
- `inicializarUI()`
- `conectarEventos()`
- `cargarDatos()`
- `validarEstado()`
- `registrarEvento(const QString &)`

Cada una sobrescrita obligatoriamente en Login, EditorPrincipal y ModoBloqueado.

## Eventos redefinidos

| Evento             | Login | EditorPrincipal | ModoBloqueado |
|--------------------|-------|-----------------|---------------|
| `closeEvent`       | ✅ (confirmar salida) | ✅ (confirmar) | ✅ (denegar) |
| `keyPressEvent`    | ✅ (Esc cierra) | ✅ (Ctrl+S exporta) | ✅ (ignora todo) |
| `mousePressEvent`  | – | ✅ (log de clicks) | – |
| `resizeEvent`      | – | ✅ | – |
| `focusInEvent`     | – | ✅ | – |
| `focusOutEvent`    | – | ✅ (dispara validación) | – |

## Archivos

- `EditorMultilenguaje.pro`
- `main.cpp` ......................... entrada
- `controlador.h/.cpp` .............. orquestador de pantallas (polimorfismo)
- `pantalla.h/.cpp` ................. clase base abstracta
- `login.h/.cpp/.ui` ................ pantalla de login con QtDesigner
- `editorprincipal.h/.cpp` .......... pantalla principal con editor + CV
- `modobloqueado.h/.cpp` ............ pantalla de bloqueo temporal
- `validadorsintaxis.h/.cpp` ........ jerarquía abstracta
- `validadorcpp.h/.cpp`
- `validadorpython.h/.cpp`
- `validadorjava.h/.cpp`
- `config.ini` ...................... usuario, bloqueo, lenguaje, exportación

## Credenciales (configurables en config.ini)

- Usuario: `admin`
- Clave: `1234`
- Tras 3 intentos fallidos → ModoBloqueado durante 15 segundos.

## Cómo se valida la sintaxis (polimorfismo en acción)

En `EditorPrincipal`:

```cpp
ValidadorSintaxis * validador;   // puntero a clase base

// Al cambiar lenguaje en el combo:
delete validador;
switch ( indice )  {
    case 0:  validador = new ValidadorCpp;    break;
    case 1:  validador = new ValidadorPython; break;
    case 2:  validador = new ValidadorJava;   break;
}

// En todo el resto del código:
validador->validarLinea( texto );  // se resuelve en runtime según el objeto real
```

## Flujo de pantallas (polimorfismo en acción)

En `Controlador`:

```cpp
Pantalla * actual;  // puntero a la clase base abstracta

void cambiarA( Pantalla * nueva )  {
    actual = nueva;
    actual->show();
    // ...
}
```

El controlador opera contra la interfaz abstracta. No sabe si por debajo es Login, Editor o ModoBloqueado.

## Validación por línea

La validación se dispara cuando el cursor abandona una línea
(`cursorPositionChanged` + chequeo de número de bloque).

- Línea válida → fondo neutro, mensaje verde "Sin errores."
- Línea inválida → fondo rojo + mensaje amigable en rojo abajo.

## Exportación a JPG

Click en "Exportar a JPG" (o Ctrl+S):
- Renderiza todo el contenido del editor con `QPainter` sobre un `QImage`.
- Abre diálogo para elegir destino.
- Guarda como JPG con calidad 92.

## Configuración (config.ini)

```ini
[login]
usuario=admin
clave=1234
maxIntentos=3
duracionBloqueo=15

[editor]
lenguaje=C++
rutaExportacion=codigo.jpg
```

⚠️ Recordá copiar `config.ini` a la carpeta `debug` donde se genera el `.exe`,
no dejarlo solo en la carpeta de fuentes.

## Log de eventos

Se genera `eventos.log` con cada acción importante:
```
[2026-06-03 18:42:11] Login: Acceso correcto
[2026-06-03 18:42:11] EditorPrincipal: Editor principal inicializado
[2026-06-03 18:42:25] EditorPrincipal: Lenguaje cambiado a Python
[2026-06-03 18:43:02] EditorPrincipal: Código exportado a C:/Users/jose/codigo.jpg
```

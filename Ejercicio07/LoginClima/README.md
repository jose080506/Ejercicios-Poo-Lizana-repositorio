# Ejercicio 07 - Login con clima y fondo de pantalla

## Arquitectura

```
Pantalla (abstracta, hereda QWidget)
├── Login   (hereda Pantalla, usa login.ui de QtDesigner)
└── Ventana (hereda Pantalla, full screen)

Clima (hereda QObject, encapsula QNetworkAccessManager)
```

## Archivos

- `LoginClima.pro` ............ proyecto qmake
- `main.cpp` .................. entrada + proxy del sistema
- `pantalla.h/.cpp` ........... clase base abstracta + log de eventos
- `login.h/.cpp/.ui` .......... ventana de login (con QtDesigner)
- `ventana.h/.cpp` ............ ventana principal full screen
- `clima.h/.cpp` .............. servicio de clima vía API
- `config.ini` ................ API key y ciudad

## Antes de compilar

1. Conseguí una API key gratuita en https://openweathermap.org/api
2. Pegala en `config.ini` en `apikey=`
3. El `.exe` compilado tiene que tener cerca el `config.ini` (en
   el directorio de build, no en el de fuentes)

## Para que las llamadas HTTPS funcionen en Windows

Hay que tener OpenSSL instalado:
https://slproweb.com/products/Win32OpenSSL.html

Bajar Win64 OpenSSL Light y poner los DLL en el PATH o al lado del .exe.

## Credenciales

- Usuario: `admin`
- Clave: `1234`
- Tras 3 intentos fallidos => bloqueo de 15 segundos.

## Modo offline

Si no hay conexión:
- El clima muestra "Modo offline (clima simulado)"
- La ventana principal usa el cache local del fondo si existe,
  o un color sólido si tampoco hay cache.

## Log de eventos

Se genera un archivo `eventos.log` en el directorio del .exe con cada
acción (login, intento fallido, descarga, etc.).

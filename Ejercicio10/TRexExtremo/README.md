# Ejercicio 10 - T-Rex Extremo

Juego inspirado en el T-Rex de Google Chrome. Dibujado todo a mano con `QPainter`
(sin imágenes externas), arquitectura modular en 4 clases.

## Arquitectura

```
Juego (QWidget) - escenario principal
  ├── TRex (QWidget)           - el dinosaurio del jugador
  │     └── QTimer propio      - física del salto (gravedad)
  ├── Cactus (QWidget) [N]     - movidos por el timer principal del Juego
  └── Pajaro (QWidget) [M]
        └── QTimer propio      - cada pájaro se mueve por sí solo

Timer principal (cada 30 ms):  mueve cactus + detecta colisiones + puntaje
Timer spawn cactus:            intervalos aleatorios entre 800 y 2300 ms
Timer spawn pájaros:           cada 5000 ms exactos (consigna)
Timer dificultad:              cada 8000 ms sube velocidadCactus
```

## Cumplimiento del checklist

| Item | Estado |
|------|--------|
| Clase TRex hereda QWidget | ✅ |
| Clase Pajaro hereda QWidget | ✅ |
| Cada Pajaro tiene su propio QTimer | ✅ (timerMovimiento + timerAleteo) |
| QTimer principal para cactus + colisiones | ✅ |
| Spawn de pájaro cada 5 segundos | ✅ (timerSpawnPajaro) |
| Salto con Espacio | ✅ |
| Agacharse con Flecha Abajo | ✅ |
| Adelantarse con Flecha Derecha | ✅ |
| Frenarse con Flecha Izquierda | ✅ |
| Detección de colisiones | ✅ (QRect::intersects con hitboxes) |
| Game Over + reiniciar | ✅ (Enter para reiniciar) |
| Velocidad creciente | ✅ (timerDificultad) |
| Tipos de pájaros + alturas aleatorias | ✅ (Chico/Medio/Grande + 4 alturas) |
| connect con SIGNAL/SLOT | ✅ |

## Controles

| Tecla              | Acción      |
|--------------------|-------------|
| Espacio o Flecha ↑ | Saltar      |
| Flecha ↓           | Agacharse (mientras se mantenga apretada) |
| Flecha →           | Adelantarse (25 px) |
| Flecha ←           | Frenarse (25 px) |
| Enter              | Reiniciar tras Game Over |

## Cómo correrlo

1. Abrí `TRexExtremo.pro` con Qt Creator
2. Compilá y corré (Ctrl+R)
3. **Importante**: hacé click en la ventana para que tenga foco antes de jugar

## Diseño técnico — puntos para el video

### Múltiples QTimer trabajando en paralelo

Lo más interesante del ejercicio es que conviven **muchos QTimer**:

- 1 timer principal del Juego (30 ms)
- 1 timer de spawn cactus (intervalo variable)
- 1 timer de spawn pájaros (5 seg exactos)
- 1 timer de dificultad (8 seg)
- 1 timer interno del T-Rex (25 ms, física del salto)
- 2 timers por cada pájaro vivo (movimiento + aleteo)

Si hay 4 pájaros en pantalla, son **4×2 + 5 = 13 timers** corriendo
simultáneamente. Esto demuestra cómo Qt maneja la concurrencia con el event loop.

### Encapsulamiento

- El T-Rex maneja su propia física: el Juego no toca la posición Y del trex.
  El Juego solo llama `trex->saltar()`, `trex->agacharse()`, etc.
- Cada Pájaro maneja su propio movimiento. El Juego no recorre los pájaros
  para moverlos: cada uno se mueve solo gracias a su `QTimer` interno.
- Solo los cactus son movidos por el timer principal del Juego (porque la
  consigna específicamente lo pide así).

### Detección de colisiones

Cada entidad implementa `hitbox()` que devuelve un `QRect` en coordenadas del
padre. La detección es simple:

```cpp
if ( trex->hitbox().intersects( cactus->hitbox() ) )  // colisión
```

Las hitboxes son **más chicas** que los rects visuales, para que el juego no
sea injusto cuando los pixeles se rozan apenas.

### Self-destruction de pájaros

Cuando un pájaro sale por la izquierda, emite un signal y el Juego lo elimina
con `deleteLater()`. Esto evita acumular pájaros muertos.

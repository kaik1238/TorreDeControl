# Experimentos — Caso 1: Torre de control de un aeropuerto

## Experimento del caso: `--puertas 1` frente a `--puertas 8`

### Predicción (registrar en un commit antes de ejecutar)

Con `--puertas 1`, solo un avión puede ocupar una puerta a la vez. Por tanto, se espera que aumente la espera de los aviones para conseguir puerta y que la puerta pueda convertirse en un cuello de botella. Los aviones que ya han conseguido puerta pueden seguir ocupándola mientras esperan a que terminen sus tres servicios y mientras embarcan.

Con `--puertas 8`, habrá más capacidad de estacionamiento. Se espera que disminuya la espera por puerta y que más aviones puedan permanecer simultáneamente en tierra. La mejora podría quedar limitada por el número de pistas, la capacidad de la cola de servicios (`--cola`) y el número de operarios (`--operarios`).

La métrica principal para comparar es la espera `avión (puerta)`. También conviene observar `avión (pista para aterrizar)`, `avión (pista para despegar)` y `avión (servicios)`, porque al reducirse el cuello de botella de puertas puede trasladarse la espera a otro recurso.

**Importante:** esta sección de predicción debe quedar guardada en un commit anterior al commit que incorpore los resultados, tal como exige el enunciado.

### Configuración y método

Ejecutar las dos configuraciones con el mismo número de aviones y los mismos valores para el resto de parámetros. Cambiar únicamente el número de puertas:

```bash
./caso1 --puertas 1
./caso1 --puertas 8
```

Si el ejecutable tiene otro nombre, sustituir `caso1` por el nombre real. Para obtener resultados comparables, repetir cada configuración varias veces con `--estres` si el programa base lo permite, y conservar las salidas completas.

### Resultados reales (rellenar después de ejecutar)

| Configuración | Espera avión (puerta), media | Espera avión (puerta), máxima | Espera pista aterrizaje | Espera pista despegue | Espera servicios | Operaciones |
|---|---:|---:|---:|---:|---:|---:|
| `--puertas 1` | Pendiente | Pendiente | Pendiente | Pendiente | Pendiente | Pendiente |
| `--puertas 8` | Pendiente | Pendiente | Pendiente | Pendiente | Pendiente | Pendiente |

**Interpretación de los resultados:** pendiente de completar con los datos reales. Indicar si se confirma la predicción y explicar cualquier diferencia. No sustituir esta sección por resultados inventados.

## Pruebas de estrés y modos de fallo

El enunciado pide incluir la salida de `--estres 10` sin fallo y la de cada modo de fallo con `--estres 10`, explicando por qué la misma configuración puede fallar unas veces sí y otras no. Añadir aquí las salidas reales del ejecutable:

### Versión correcta

Comando:

```bash
./caso1 --estres 10
```

Salida real:

```text
PENDIENTE: pegar aquí la salida real.
```

### Modo `carrera`

Comando:

```bash
./caso1 --fallo carrera --estres 10
```

Salida real:

```text
PENDIENTE: pegar aquí la salida real.
```

El modo de fallo del caso elimina la protección del contador de operaciones. El resultado depende del intercalado de los hilos: dos incrementos concurrentes pueden leer el mismo valor y sobrescribirse, perdiéndose una actualización.

### Modo `interbloqueo`

Comando:

```bash
./caso1 --fallo interbloqueo --estres 10
```

Salida real:

```text
PENDIENTE: pegar aquí la salida real.
```

El modo de fallo reproduce la adquisición de la pista antes de solicitar la puerta después del aterrizaje sin liberar la pista. Puede dejar recursos retenidos mientras los hilos esperan otros recursos, impidiendo el progreso. El vigilante debe detectar la falta de progreso.

### Modo `inanicion`

Comando:

```bash
./caso1 --fallo inanicion --estres 10 --pistas 1 --puertas 40 --aviones 40
```

Salida real:

```text
PENDIENTE: pegar aquí la salida real.
```

El modo de fallo favorece siempre a los aterrizajes cuando coinciden aterrizajes y despegues. Los aviones que esperan para despegar pueden quedar pospuestos repetidamente. La espera máxima de despegue debe permitir observar la inanición.

## Competición

El enunciado también pide registrar la mediana de la versión del equipo con 1, 2, 4 y 8 hilos, indicando el número de núcleos del ordenador. Incorporar las cinco mediciones de cada configuración y calcular la mediana.

- Procesador / número de núcleos: Pendiente.
- Resultado de comprobación (`--comprobar`): Pendiente.

| Hilos | Medición 1 | Medición 2 | Medición 3 | Medición 4 | Medición 5 | Mediana |
|---:|---:|---:|---:|---:|---:|---:|
| 1 | — | — | — | — | — | — |
| 2 | — | — | — | — | — | — |
| 4 | — | — | — | — | — | — |
| 8 | — | — | — | — | — | — |

Explicar los tiempos observados y si aumentar los hilos mejora el rendimiento en el equipo utilizado.

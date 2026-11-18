# Diseño — Caso 1: Torre de control de un aeropuerto

> Documento de trabajo del equipo. Esta versión desarrolla el monitor de `ServiciosTierra`, que es la parte asignada a este miembro. Las filas de los monitores de `TorreControl` y del panel deben completarse y revisarse con las personas responsables de esas clases antes de entregar.

## Monitor `ServiciosTierra`

El estado protegido por el monitor es la cola FIFO de servicios, su capacidad, el número de servicios pendientes de cada avión y el indicador de cierre. Todos esos datos se consultan o modifican manteniendo `mutex_`.

| Operación | Espera mientras… | Quién avisa |
|---|---|---|
| Encolar un servicio (`encargarYEsperarServicios`) | La cola tenga `capacidad` elementos y no esté cerrada. La espera se realiza con `hayEspacio_`. | Un operario avisa con `hayEspacio_.notify_one()` después de extraer un servicio. |
| Extraer un servicio (`ejecutarOperario`) | La cola esté vacía y no esté cerrada. La espera se realiza con `hayTrabajo_`. | Un avión avisa con `hayTrabajo_.notify_one()` después de encolar un servicio. `cerrarCola()` avisa a todos para permitir la salida de los operarios. |
| Esperar a que terminen los tres servicios del avión | El contador de servicios pendientes de ese avión sea mayor que cero. La espera se realiza con `serviciosTerminados_`. | El operario que termina el último servicio de ese avión llama a `serviciosTerminados_.notify_all()`. |
| Cerrar la cola | No es una espera: se establece `cerrada_ = true`. | `cerrarCola()` llama a `notify_all()` sobre las condiciones para despertar a operarios y posibles productores bloqueados. |

### Propiedades e invariantes

- La cola es FIFO: cada operario extrae siempre `cola_.front()`.
- La cola nunca supera `capacidad`.
- El contador de pendientes de un avión representa los servicios que se han encolado y todavía no han terminado.
- El avión no retorna de `encargarYEsperarServicios` hasta que su contador de pendientes llega a cero.
- Los operarios solo terminan cuando `cerrada_` es verdadera y la cola está vacía.
- Cada servicio completado incrementa `operaciones` en una unidad y llama a `Vigilante::progreso()`.

### Orden de cierre

Según el enunciado, cuando hayan despegado todos los aviones, `main` cierra la cola de servicios y el panel. Para los servicios, el orden de integración debe ser:

1. Esperar (`join`) a todos los hilos de avión.
2. Llamar a `cerrarCola()`.
3. Esperar (`join`) a todos los hilos de operario.

No se debe cerrar la cola mientras los aviones todavía puedan solicitar servicios.

## Otros monitores del caso

Completar estas filas junto con las personas responsables de `TorreControl` antes de la entrega final. No inventar las condiciones: deben coincidir con los predicados reales del código.

| Monitor | Operación | Espera mientras… | Quién avisa |
|---|---|---|---|
| `TorreControl` — pistas | Solicitar pista para aterrizar | Pendiente de completar a partir del predicado implementado y la política de alternancia. | Pendiente de completar. |
| `TorreControl` — pistas | Solicitar pista para despegar | Pendiente de completar a partir del predicado implementado y la política de alternancia. | Pendiente de completar. |
| `TorreControl` — puertas (`Semaforo`) | Adquirir una puerta | No haya un permiso disponible. | El avión que libera una puerta llama a `release()`. |
| Panel (`shared_mutex`) | Leer estado de vuelos | No espera mediante una variable de condición; la lectura comparte el bloqueo de lectura. | Los escritores liberan su bloqueo al terminar de actualizar. |
| Panel (`shared_mutex`) | Actualizar estado o añadir aviso | No espera mediante una variable de condición; espera a obtener el bloqueo exclusivo. | Los lectores y escritores liberan sus bloqueos al terminar. |

> La tabla definitiva debe describir todos los monitores del proyecto y utilizar exactamente los predicados y avisos que aparezcan en la implementación final.

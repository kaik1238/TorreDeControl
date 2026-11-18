# Registro de uso de herramientas de IA

Este documento registra las consultas de IA relacionadas con la parte `ServiciosTierra` y la documentación. El enunciado exige que por cada consulta consten fecha, miembro, herramienta, prompt exacto, respuesta o parte relevante, qué se incorporó, qué se descartó o corrigió y los ficheros y commits afectados.

> Completar el miembro responsable y los identificadores reales de commit. El equipo debe añadir aquí cualquier otra consulta de IA que haya realizado; este registro no sustituye las entradas de los demás miembros.

## Consulta 1 — Diseño e implementación de `ServiciosTierra`

- **Fecha:** 18/11/2026
- **Miembro:** completar con el nombre del miembro que realizó la consulta.
- **Herramienta:** ChatGPT (OpenAI).
- **Prompt exacto:** «hazme la clase ServiciosTierra.h y ServiciosTierra.cpp del caso 1 siguiendo el enunciado. Tiene que gestionar la cola de servicios de los aviones, controlar que tenga capacidad limitada, que los operarios atiendan los servicios por orden de llegada y que cada avión espere hasta que tenga los tres servicios terminados, utiliza mutex y condition_variable para sincronizarlo y las clases auxiliares del proyecto. También explícame cómo conectarlo con el main y cómo cerrar los hilos correctamente.»
- **Respuesta obtenida (resumen relevante):** se propuso una clase `ServiciosTierra` con una cola FIFO acotada, un contador de servicios pendientes por avión, una condición para esperar espacio, otra para esperar trabajo y otra para esperar la finalización de los servicios. Se prepararon los ficheros `ServiciosTierra.h` y `ServiciosTierra.cpp`, además de una guía de integración.
- **Qué se incorporó:** la estructura general de la cola acotada, el uso de `condition_variable` con predicados, el seguimiento de servicios pendientes por avión y el cierre de la cola.
- **Qué se debe revisar o adaptar:** las firmas de `Estadisticas`, `Traza` y `Vigilante` deben comprobarse contra las clases auxiliares reales del proyecto base. También hay que compilar con el `CMakeLists.txt` del profesor, comprobar los avisos de compilación y probar el cierre y la ejecución concurrente con varios aviones y operarios. La implementación no debe darse por validada hasta pasar esas pruebas.
- **Ficheros relacionados:** `ServiciosTierra.h`, `ServiciosTierra.cpp`, `DISENO.md`.
- **Commit:** pendiente de completar con el hash real.

## Consulta 2 — Documentación requerida

- **Fecha:** 18/11/2026
- **Miembro:** completar con el nombre del miembro que realizó la consulta.
- **Herramienta:** ChatGPT (OpenAI).
- **Prompt exacto:** «vale pues pasme el zip bueno»
- **Respuesta obtenida (resumen relevante):** se preparó un paquete con `ServiciosTierra.h`, `ServiciosTierra.cpp`, `DISENO.md`, `EXPERIMENTOS.md` e `IA.md`, basándose en el enunciado del Caso 1.
- **Qué se incorporó:** una primera tabla de predicados para el monitor de `ServiciosTierra`, una predicción razonada para comparar `--puertas 1` y `--puertas 8`, y el registro de las consultas de IA.
- **Qué se descartó o dejó pendiente:** no se inventaron resultados de ejecución, estadísticas, mediciones de competición, nombres de miembros ni hashes de commits. Los campos pendientes deben completarse con datos reales del equipo. Las filas de `TorreControl` y panel deben revisarse con la implementación final.
- **Ficheros relacionados:** `DISENO.md`, `EXPERIMENTOS.md`, `IA.md`, `ServiciosTierra.h`, `ServiciosTierra.cpp`.
- **Commit:** pendiente de completar con el hash real.

## Registro de consultas adicionales

Añadir una sección por cada nueva consulta de IA, incluyendo el prompt literal y la respuesta relevante. Si se modifica código o documentación generados con IA, actualizar también la entrada correspondiente para que el historial permita rastrear el contenido hasta el commit en el repositorio.

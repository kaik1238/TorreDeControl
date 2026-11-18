# ServiciosTierra — integración

Constructor:
`ServiciosTierra(int capacidad, Estadisticas&, Traza&, Vigilante&)`

Métodos:
- `encargarYEsperarServicios(idAvion)`: lo llama el hilo del avión.
- `ejecutarOperario()`: se ejecuta en un hilo independiente.
- `cerrarCola()`: se llama cuando todos los aviones han terminado.

Ejemplo de integración futura en `main.cpp`:

```cpp
ServiciosTierra servicios(capacidadCola, estadisticas, traza, vigilante);
std::thread operario(&ServiciosTierra::ejecutarOperario, &servicios);

// Crear los aviones y lanzar sus hilos.
// Hacer join de todos los hilos de aviones.

servicios.cerrarCola();
operario.join();
```

La capacidad se interpreta como número de trabajos individuales en la cola.
Cada avión solicita combustible (9 ms), limpieza (3 ms) y catering (3 ms).
El operario los procesa en FIFO y el avión espera hasta completar los tres.

IMPORTANTE: las llamadas utilizadas siguen las interfaces descritas en el enunciado:
- `registrarEspera(string, duration)`
- `sumar(string, int)`
- `evento(string, string)`
- `progreso()`

Hay que contrastarlas con los `.h` reales de las clases auxiliares del proyecto base.

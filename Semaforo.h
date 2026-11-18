#pragma once

#include <mutex>
#include <condition_variable>
#include <chrono>

class Semaforo {
private:
    int valor;                      // S.contador: permisos disponibles (nunca negativo)
    std::mutex mtx;                 // Exclusión mutua para proteger el contador
    std::condition_variable cv;     // S.cola: hilos dormidos esperando un permiso

public:
    // Se crea con un valor inicial (ej. 1 para cerrojo/binario, 0 para aviso, N para contador)
    explicit Semaforo(int valorInicial = 0);

    void acquire();                                   // Equivalente a wait() / P()
    void release();                                   // Equivalente a signal() / V()
    bool tryAcquireFor(std::chrono::milliseconds timeout); // Intento con tiempo límite
};
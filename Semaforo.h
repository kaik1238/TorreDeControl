#pragma once

#include <mutex>
#include <condition_variable>
#include <chrono>

// Clase Semaforo implementada como un monitor (mutex + variable de condición)
class Semaforo {
private:
    int valor;                        // Contador de permisos/recursos disponibles
    std::mutex mtx;                   // Cerrojo para proteger el acceso exclusivo a 'valor'
    std::condition_variable cv;       // Variable de condición para suspender/despertar hilos

public:
    // Constructor: inicializa el contador del semáforo (por defecto a 0)
    explicit Semaforo(int valorInicial = 0);

    // Operación P (wait): pide un permiso; si valor == 0, bloquea el hilo hasta que haya hueco
    void acquire();

    // Operación V (signal): libera un permiso y despierta a un hilo que esté esperando
    void release();

    // Intenta conseguir un permiso esperando como máximo 'timeout' milisegundos
    bool tryAcquireFor(std::chrono::milliseconds timeout);
};
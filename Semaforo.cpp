#include "Semaforo.h"

using namespace std;

Semaforo::Semaforo(int valorInicial) : valor(valorInicial) {}

void Semaforo::acquire() {
    // 1. Entramos en la sección protegida por el mutex del monitor
    unique_lock<mutex> lock(mtx);

    // 2. Si S.contador == 0, el hilo se duerme en la cola sin consumir CPU.
    // El predicado [this]() { return valor > 0; } evita despertares espurios.
    cv.wait(lock, [this]() { return valor > 0; });

    // 3. Cuando se despierta, coge un permiso decrementando el contador
    valor--;
}

void Semaforo::release() {
    // 1. Protegemos el incremento con el mutex
    unique_lock<mutex> lock(mtx);

    // 2. Devolvemos el permiso subiendo el contador
    valor++;

    // 3. Si hay hilos en la cola (S.cola), despierta a uno de ellos
    cv.notify_one();
}

bool Semaforo::tryAcquireFor(chrono::milliseconds timeout) {
    unique_lock<mutex> lock(mtx);

    // Espera hasta que el contador > 0 o se agote el tiempo límite
    if (!cv.wait_for(lock, timeout, [this]() { return valor > 0; })) {
        return false; // Si caducó el tiempo y seguía a 0, devuelve false
    }

    valor--;
    return true;
}
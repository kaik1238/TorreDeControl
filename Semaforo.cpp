#include "Semaforo.h"

using namespace std;
using namespace std::chrono;

// Inicializamos el contador del semáforo con el valor recibido
Semaforo::Semaforo(int valorInicial) : valor(valorInicial) {}

void Semaforo::acquire() {
    // Adquirimos el cerrojo de forma segura mediante RAII (unique_lock)
    unique_lock<mutex> lock(mtx);

    // Si valor <= 0, el hilo libera el mutex y se duerme sin espera activa.
    // La expresión lambda evita despertares espurios comprobando que valor > 0.
    cv.wait(lock, [this]() { return valor > 0; });

    // Una vez dentro y con permiso disponible, decrementamos el contador
    valor--;
}

void Semaforo::release() {
    // Protegemos la modificación del contador con el mutex
    unique_lock<mutex> lock(mtx);

    // Devolvemos un permiso al semáforo
    valor++;

    // Avisamos a uno de los hilos que estén dormidos en acquire() o tryAcquireFor()
    cv.notify_one();
}

bool Semaforo::tryAcquireFor(milliseconds timeout) {
    unique_lock<mutex> lock(mtx);

    // Espera hasta que valor > 0 o hasta que se agote el tiempo 'timeout'.
    // Si se agota el tiempo y valor sigue siendo <= 0, wait_for devuelve false.
    if (!cv.wait_for(lock, timeout, [this]() { return valor > 0; })) {
        return false;
    }

    // Si consiguió despertarse con valor > 0 antes del límite, consume el permiso
    valor--;
    return true;
}
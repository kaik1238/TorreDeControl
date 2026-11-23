#include "Semaforo.h"

// TODO: implementar. Ahora mismo compila, pero no sincroniza nada.

Semaforo::Semaforo(int valorInicial) : _valor(valorInicial) {}

void Semaforo::acquire() {
    (void)_valor;  // TODO: quitad esta línea al implementar
}

void Semaforo::release() {
    // TODO
}

bool Semaforo::tryAcquireFor(std::chrono::milliseconds plazo) {
    (void)plazo;  // TODO
    return false;
}

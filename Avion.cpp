#include "Avion.h"

#include <chrono>
#include <thread>

#include "ServiciosTierra.h"
#include "TorreControl.h"

void Avion::ejecutar() {
    using std::chrono::milliseconds;

    // 1. Espera 2i ms y pone en el panel "en aproximación"
    std::this_thread::sleep_for(milliseconds(2 * id_));
    torre_.actualizarPanel(id_, "en aproximación");

    // 2. Consigue una puerta y después una pista
    torre_.pedirPuerta(id_);
    int pista = torre_.pedirPistaAterrizaje(id_);

    // 3. Aterriza (2 ms), libera la pista y pone en el panel "en puerta"
    std::this_thread::sleep_for(milliseconds(2));
    torre_.liberarPista(pista);
    torre_.registrarOperacion();
    torre_.actualizarPanel(id_, "en puerta");

    // 4. Encarga sus 3 servicios a la cola y espera a que estén hechos
    servicios_.encargarYEsperarServicios(id_);

    // 5. Embarca (2 ms)
    std::this_thread::sleep_for(milliseconds(2));

    // 6. Consigue pista, libera puerta, despega (2 ms), libera pista y pone "despegado"
    pista = torre_.pedirPistaDespegue(id_);
    torre_.liberarPuerta(id_);
    std::this_thread::sleep_for(milliseconds(2));
    torre_.liberarPista(pista);
    torre_.registrarOperacion();
    torre_.actualizarPanel(id_, "despegado");
}

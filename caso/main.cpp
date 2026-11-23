// main del caso. Vuestro trabajo: rellenar ejecutarSimulacion y las listas de claves y modos.
// Mirad ejemplo/main.cpp para ver cómo se usan las clases del proyecto base.
// Vuestras 3 clases van en esta misma carpeta (caso/), cada una en su .h y su .cpp,
// y sus .cpp se añaden a caso/CMakeLists.txt.

#include "Config.h"
#include "Estadisticas.h"
#include "Lanzador.h"
#include "Traza.h"
#include "Vigilante.h"

#include <chrono>
#include <string>

bool ejecutarSimulacion(const Config& config, Estadisticas& estadisticas, Traza& traza, const std::string& etiqueta) {
    (void)traza;
    Vigilante vigilante(std::chrono::milliseconds(config.entero("vigilante", 2000)), estadisticas, etiqueta);
    vigilante.iniciar();

    // TODO: crear los objetos, lanzar los hilos, cierre ordenado, invariantes finales.

    vigilante.detener();
    return estadisticas.sinViolaciones();
}

int main(int argc, char* argv[]) {
    Config config(argc, argv);
    // TODO: poner el nombre del caso, sus 6 claves y sus modos de fallo (el caso 5 añade "livelock").
    Lanzador lanzador("caso", {}, {"carrera", "interbloqueo", "inanicion"});
    return lanzador.ejecutar(config, ejecutarSimulacion);
}

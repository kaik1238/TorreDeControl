#pragma once

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <queue>
#include <unordered_map>

using namespace std;

class Estadisticas;
class Traza;
class Vigilante;

class ServiciosTierra {
public:
    ServiciosTierra(int capacidad, Estadisticas& estadisticas,
                    Traza& traza, Vigilante& vigilante);

    ServiciosTierra(const ServiciosTierra&) = delete;
    ServiciosTierra& operator=(const ServiciosTierra&) = delete;

    void encargarYEsperarServicios(int idAvion);
    void ejecutarOperario();
    void cerrarCola();

private:
    struct Servicio {
        int idAvion;
        const char* nombre;
        int duracionMs;
    };

    const int capacidad_;
    Estadisticas& estadisticas_;
    Traza& traza_;
    Vigilante& vigilante_;

    mutex mutex_;
    condition_variable hayEspacio_;
    condition_variable hayTrabajo_;
    condition_variable serviciosTerminados_;

    queue<Servicio> cola_;
    unordered_map<int, int> pendientesPorAvion_;
    bool cerrada_ = false;
};

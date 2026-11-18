#include "ServiciosTierra.h"

#include <array>
#include <chrono>
#include <stdexcept>
#include <string>
#include <thread>

#include "Estadisticas.h"
#include "Traza.h"
#include "Vigilante.h"

ServiciosTierra::ServiciosTierra(int capacidad, Estadisticas& estadisticas,
                                 Traza& traza, Vigilante& vigilante)
    : capacidad_(capacidad),
      estadisticas_(estadisticas),
      traza_(traza),
      vigilante_(vigilante) {
    if (capacidad_ <= 0) {
        throw std::invalid_argument("La capacidad de la cola debe ser mayor que cero");
    }
}

void ServiciosTierra::encargarYEsperarServicios(int idAvion) {
    using reloj = std::chrono::steady_clock;
    const auto inicioEspera = reloj::now();

    const std::array<Servicio, 3> servicios{{
        {idAvion, "combustible", 9},
        {idAvion, "limpieza", 3},
        {idAvion, "catering", 3}
    }};

    {
        std::unique_lock<std::mutex> lock(mutex_);
        pendientesPorAvion_[idAvion] = 3;

        for (const Servicio& servicio : servicios) {
            hayEspacio_.wait(lock, [this] {
                return cerrada_ || cola_.size() < static_cast<std::size_t>(capacidad_);
            });

            if (cerrada_) {
                pendientesPorAvion_.erase(idAvion);
                throw std::logic_error("La cola de servicios está cerrada");
            }

            cola_.push(servicio);
            traza_.evento("avion " + std::to_string(idAvion),
                          std::string("solicita ") + servicio.nombre);
            hayTrabajo_.notify_one();
        }

        serviciosTerminados_.wait(lock, [this, idAvion] {
            const auto it = pendientesPorAvion_.find(idAvion);
            return it != pendientesPorAvion_.end() && it->second == 0;
        });

        pendientesPorAvion_.erase(idAvion);
    }

    estadisticas_.registrarEspera(
        "avion (servicios)",
        std::chrono::duration_cast<std::chrono::milliseconds>(
            reloj::now() - inicioEspera)
    );
}

void ServiciosTierra::ejecutarOperario() {
    for (;;) {
        Servicio servicio{};

        {
            std::unique_lock<std::mutex> lock(mutex_);
            hayTrabajo_.wait(lock, [this] {
                return cerrada_ || !cola_.empty();
            });

            if (cerrada_ && cola_.empty()) {
                return;
            }

            servicio = cola_.front();
            cola_.pop();
            hayEspacio_.notify_one();
        }

        traza_.evento("operario",
                      std::string("inicia ") + servicio.nombre +
                      " del avion " + std::to_string(servicio.idAvion));

        // Simula la duración del servicio indicada en el enunciado.
        std::this_thread::sleep_for(std::chrono::milliseconds(servicio.duracionMs));

        {
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = pendientesPorAvion_.find(servicio.idAvion);
            if (it != pendientesPorAvion_.end() && it->second > 0) {
                --it->second;
                if (it->second == 0) {
                    serviciosTerminados_.notify_all();
                }
            }
        }

        estadisticas_.sumar("operaciones", 1);
        vigilante_.progreso();

        traza_.evento("operario",
                      std::string("termina ") + servicio.nombre +
                      " del avion " + std::to_string(servicio.idAvion));
    }
}

void ServiciosTierra::cerrarCola() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        cerrada_ = true;
    }
    hayTrabajo_.notify_all();
    hayEspacio_.notify_all();
}

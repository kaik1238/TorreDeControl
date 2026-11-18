#pragma once

#include <string>
#include <vector>
#include <shared_mutex>
#include "Config.h"

class TorreControl {
private:
    // Estado compartido del panel protegido por std::shared_mutex (muchos leen, pocos escriben).
    mutable std::shared_mutex mtx_panel_;
    std::vector<std::string> estados_aviones_;
    std::vector<std::string> avisos_torre_;

    // Contador de operaciones y modo de fallo.
    int operaciones_;
    bool modo_carrera_;

    // Control de finalización para los hilos secundarios (pantallas y operador).
    bool cerrado_;

public:
    // Constructor que recibe la configuración para evaluar el modo de fallo carrera.
    explicit TorreControl(const Config& config, int num_aviones);

    // Métodos para los hilos de Pantalla y Operador de Torre.
    void ejecutarPantalla(int id_pantalla);
    void ejecutarOperadorTorre();

    // Gestión del panel de vuelos.
    void actualizarEstadoAvion(int id_avion, const std::string& estado);
    void agregarAviso(const std::string& aviso);
    std::vector<std::string> leerPanel() const;

    // Métodos de operaciones, control y cierre.
    void incrementarOperaciones();
    int obtenerOperaciones() const;
    void cerrar();

    // Esqueletos de integración para las pistas y puertas (requeridos para la clase Avion).
    void pedirPuerta();
    void liberarPuerta();
    void pedirPistaAterrizaje();
    void pedirPistaDespegue();
    void liberarPista();
};
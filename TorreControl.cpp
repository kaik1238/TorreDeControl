#include "TorreControl.h"
#include "Traza.h"     // Clase auxiliar del proyecto base para trazas.
#include "Vigilante.h" // Clase auxiliar para reportar progreso.
#include <thread>
#include <chrono>

TorreControl::TorreControl(const Config& config, int num_aviones)
    : operaciones_(0),
      modo_carrera_(config.fallo("carrera")),
      cerrado_(false) {
    // Inicializamos el vector de estados de los aviones.
    estados_aviones_.resize(num_aviones, "inicial");
}

void TorreControl::ejecutarPantalla(int id_pantalla) {
    // Cada pantalla lee el panel cada 1 ms hasta que se cierre la torre.
    while (!cerrado_) {
        {
            // Lectura concurrente segura usando std::shared_lock (permite múltiples lectores).
            std::shared_lock<std::shared_mutex> lock(mtx_panel_);
            // Simulamos la lectura de todos los vuelos.
            volatile size_t total_vuelos = estados_aviones_.size();
            (void)total_vuelos; 
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void TorreControl::ejecutarOperadorTorre() {
    int contador_aviso = 0;
    // El operador publica un aviso cada 30 ms hasta que se cierre la torre.
    while (!cerrado_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        if (cerrado_) break;

        std::string aviso = "Aviso oficial de torre #" + std::to_string(contador_aviso++);
        agregarAviso(aviso);
        Traza::evento("OperadorTorre", "Publica aviso: " + aviso);
    }
}

void TorreControl::actualizarEstadoAvion(int id_avion, const std::string& estado) {
    // Escritura en el panel con std::unique_lock (exclusión mutua exclusiva).
    std::unique_lock<std::shared_mutex> lock(mtx_panel_);
    if (id_avion >= 0 && id_avion < static_cast<int>(estados_aviones_.size())) {
        estados_aviones_[id_avion] = estado;
    }
}

void TorreControl::agregarAviso(const std::string& aviso) {
    std::unique_lock<std::shared_mutex> lock(mtx_panel_);
    avisos_torre_.push_back(aviso);
}

std::vector<std::string> TorreControl::leerPanel() const {
    std::shared_lock<std::shared_mutex> lock(mtx_panel_);
    // Devolvemos una copia para seguridad de hilos fuera del cerrojo.
    return estados_aviones_;
}

void TorreControl::incrementarOperaciones() {
    if (modo_carrera_) {
        // --- MODO DE FALLO: CARRERA ---
        // Se incrementa el contador sin protección de cerrojo a propósito.
        // Al leer, modificar y escribir de forma no atómica entre varios hilos, 
        // se producen condiciones de carrera que rompen el invariante final.
        int temp = operaciones_;
        std::this_thread::yield(); // Forzamos un cambio de contexto para acentuar el fallo.
        operaciones_ = temp + 1;
    } else {
        // Versión correcta (aquí en el hito 1 puedes usar un mutex interno o dejarlo simple. 
        // si se protege adecuadamente; para cumplir estrictamente sin variables globales, 
        // se suele proteger con un std::mutex privado en la clase).
        static std::mutex mtx_op;
        std::lock_guard<std::mutex> lock(mtx_op);
        operaciones_++;
    }
    Vigilante::progreso(); // Notificamos progreso al vigilante para evitar falsos interbloqueos.
}

int TorreControl::obtenerOperaciones() const {
    return operaciones_;
}

void TorreControl::cerrar() {
    cerrado_ = true;
}
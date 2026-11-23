#include "TorreControl.h"
#include "Traza.h"
#include "Vigilante.h"
#include <thread>
#include <chrono>

TorreControl::TorreControl(const Config& config, int num_aviones)
    : operaciones_(0),
      modo_carrera_(config.fallo("carrera")),
      cerrado_(false) {

    estados_aviones_.resize(num_aviones, "inicial");
}

void TorreControl::ejecutarPantalla(int id_pantalla) {
    while (!cerrado_) {
        {
            std::shared_lock<shared_mutex> lock(mtx_panel_);
            volatile size_t total_vuelos = estados_aviones_.size();
            (void)total_vuelos;
        }
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

void TorreControl::ejecutarOperadorTorre() {
    int contador_aviso = 0;

    while (!cerrado_) {
        this_thread::sleep_for(chrono::milliseconds(30));
        if (cerrado_) break;

        string aviso = "Aviso oficial de torre #" + to_string(contador_aviso++);
        agregarAviso(aviso);
        Traza::evento("OperadorTorre", "Publica aviso: " + aviso);
    }
}

void TorreControl::actualizarEstadoAvion(int id_avion, const string& estado) {
    unique_lock<shared_mutex> lock(mtx_panel_);

    if (id_avion >= 0 && id_avion < static_cast<int>(estados_aviones_.size())) {
        estados_aviones_[id_avion] = estado;
    }
}

void TorreControl::agregarAviso(const string& aviso) {
    unique_lock<shared_mutex> lock(mtx_panel_);
    avisos_torre_.push_back(aviso);
}

vector<string> TorreControl::leerPanel() const {
    shared_lock<shared_mutex> lock(mtx_panel_);
    return estados_aviones_;
}

void TorreControl::incrementarOperaciones() {
    if (modo_carrera_) {
        int temp = operaciones_;
        this_thread::yield();
        operaciones_ = temp + 1;
    } else {
        static mutex mtx_op;
        lock_guard<mutex> lock(mtx_op);
        operaciones_++;
    }

    Vigilante::progreso();
}

int TorreControl::obtenerOperaciones() const {
    return operaciones_;
}

void TorreControl::cerrar() {
    cerrado_ = true;
}

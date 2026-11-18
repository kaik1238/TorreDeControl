#pragma once

class TorreControl;
class ServiciosTierra;
class Estadisticas;
class Traza;
class Vigilante;

class Avion {
public:
    Avion(int id,
          TorreControl& torre,
          ServiciosTierra& servicios,
          Estadisticas& estadisticas,
          Traza& traza,
          Vigilante& vigilante);

    // Hilo del avión: ejecuta los pasos 1 a 6 (a - f)
    void ejecutar();

    int id() const { return id_; }

private:
    int id_;
    TorreControl& torre_;
    ServiciosTierra& servicios_;
    Estadisticas& estadisticas_;
    Traza& traza_;
    Vigilante& vigilante_;
};
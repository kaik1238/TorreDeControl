# Programación Concurrente y Distribuida - Trabajo en Equipo
## Caso 1: Torre de control de un aeropuerto

## 👥 Integrantes del Equipo
* Enrique Olmo
* Chengjun Linhuang
* Marc SANCHIS
* Alejandro Michel Ruiz
* Pili Asensi 

---

## 📋 Descripción del Proyecto
Este repositorio contiene el **Caso 1** de la asignatura de Programación Concurrente y Distribuida. El proyecto simula la gestión concurrente de un aeropuerto con $P$ pistas y $K$ puertas de embarque donde los aviones llegan, aterrizan, reciben servicios de tierra (combustible, limpieza y catering), embarcan y despegan, actualizando un panel de vuelos compartido.

El proyecto implementa estrictamente:
* **Hilos independientes** para aviones, operarios de servicios de tierra, pantallas de consulta y operador de torre.
* **Exclusión mutua con RAII** (`std::lock_guard`, `std::unique_lock`).
* **Monitores con variables de condición** (para el control de pistas alternando aterrizajes/despegues y la cola acotada de servicios de tierra).
* **Clase `Semaforo` propia** implementada como monitor (`mutex` + variable de condición) para la gestión de las $K$ puertas de embarque.
* **Lectores-escritores con `std::shared_mutex`** para el acceso concurrente al panel de vuelos.

---

## 🛠️ Compilación
El proyecto utiliza **CMake** y compila sin avisos bajo los flags estrictos `-Wall -Wextra -Wpedantic`:

```bash
mkdir build
cd build
cmake ..
cmake --build .

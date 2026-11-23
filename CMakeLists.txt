# Proyecto base — Trabajo en equipo Temas 3 a 8
# Este fichero NO se modifica. Cada carpeta tiene su propio CMakeLists.txt.

cmake_minimum_required(VERSION 3.16)
project(TrabajoTemas3a8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Modo Release por defecto (la competición se mide así)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(Threads REQUIRED)

add_subdirectory(base)             # biblioteca "base": clases auxiliares (no se modifica)
add_subdirectory(semaforo)         # biblioteca "semaforo": vuestra clase Semaforo
add_subdirectory(prueba_semaforo)  # ejecutable "prueba_semaforo"
add_subdirectory(caso)             # ejecutable de vuestro caso
add_subdirectory(competicion)      # ejecutable "competicion"
add_subdirectory(ejemplo)          # ejecutable "ejemplo" (solo para mirar)

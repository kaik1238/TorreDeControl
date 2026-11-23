# Vuestro caso. Es el ÚNICO CMakeLists.txt que se modifica:
#   1. el nombre del ejecutable;
#   2. la lista de ficheros: main.cpp y, de cada una de vuestras 3 clases, su .h y su .cpp
#      (los .h también, para que el IDE los muestre en el proyecto).

set(NOMBRE_EJECUTABLE caso)   # aeropuerto, cocina, banco, ferrocarril o almacen

add_executable(${NOMBRE_EJECUTABLE}
    main.cpp
    # Clase1.h
    # Clase1.cpp
    # Clase2.h
    # Clase2.cpp
    # Clase3.h
    # Clase3.cpp
)
target_link_libraries(${NOMBRE_EJECUTABLE} PRIVATE base semaforo)

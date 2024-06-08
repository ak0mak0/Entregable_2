#ifndef STATS_H
#define STATS_H

#include "user_data.h"
#include <cstdint>
#include <string>

struct stats {
    size_t size1000;        // Tamaño de estructura de datos en bytes al insetar los primeros 1.000
    size_t size5000;        // Tamaño de estructura de datos en bytes al insetar los primeros 5.000
    size_t size10000;       // Tamaño de estructura de datos en bytes al insetar los primeros 10.000
    size_t size15000;       // Tamaño de estructura de datos en bytes al insetar los primeros 15.000
    size_t size20000;       // Tamaño de estructura de datos en bytes al insetar los primeros 20.000
    uint64_t time1000;      // Tiempo que toma insertar los primeros 1.000 en nanosegundos
    uint64_t time5000;      // Tiempo que toma insertar los primeros 5.000 en nanosegundos
    uint64_t time10000;     // Tiempo que toma insertar los primeros 10.000 en nanosegundos
    uint64_t time15000;     // Tiempo que toma insertar los primeros 15.000 en nanosegundos
    uint64_t time20000;     // Tiempo que toma insertar los primeros 20.000 en nanosegundos
    uint64_t average_put;   // Promedio de tiempo por inserción en nanosegundos
};

#endif // STATS_H
#ifndef READCSV_H
#define READCSV_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include "user_data.h"
#include "stats.h"

// Lee un archivo CSV y realiza inserciones en una tabla hash
template <typename HashTable>
stats readCSV(HashTable &table, int const dataset) {
    int total = 0;
    // Abre el archivo CSV
    std::ifstream file("/home/ak0mak0/Escritorio/Entregable_2/Complements/universities_followers.csv");
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo universities_followers.csv" << std::endl;
        return {};
    }
    // Ignora la primera línea (encabezados)
    std::string line;
    std::getline(file, line);

    auto start_total = std::chrono::high_resolution_clock::now(); // Inicio del tiempo total
    double total_insertion_time = 0.0; // Tiempo total de inserción

    stats statistics = {};

    while (std::getline(file, line)) {
        if (!file.good())
            break;
        std::istringstream iss(line);
        std::string field;
        std::string fields[7];
        int i = 0;
        // Extrae los campos de cada línea
        while (std::getline(iss, field, ',')) {
            fields[i] = field;
            i++;
        }

        int number_tweets, friends_count, followers_count;
        // Convierte los campos a los tipos correspondientes
        std::istringstream(fields[3]) >> number_tweets;
        std::istringstream(fields[4]) >> friends_count;
        std::istringstream(fields[5]) >> followers_count;

        // Crea un objeto UserData con los datos extraídos
        UserData user_data(fields[0], fields[1], fields[2], number_tweets, friends_count, followers_count, fields[6]);

        auto start_insert = std::chrono::high_resolution_clock::now(); // Inicio del tiempo de inserción
        table.put(fields[dataset], user_data); // Inserta en la tabla hash
        auto end_insert = std::chrono::high_resolution_clock::now(); // Fin del tiempo de inserción

        // Calcula el tiempo de inserción y lo suma al tiempo total de inserción
        std::chrono::duration<double, std::nano>  elapsed_insert = end_insert - start_insert;
        total_insertion_time += elapsed_insert.count();
        total++;

        // Calcula los tiempos de inserción en puntos específicos y actualiza el tamaño de la tabla
        if (total == 1000) {
            statistics.time1000 = total_insertion_time;
            statistics.size1000 = sizeof(table) + table.getSize() * sizeof(UserData);
        }
        if (total == 5000) {
            statistics.time5000 = total_insertion_time;
            statistics.size5000 = sizeof(table) + table.getSize() * sizeof(UserData);
        }
        if (total == 10000) {
            statistics.time10000 = total_insertion_time;
            statistics.size10000 = sizeof(table) + table.getSize() * sizeof(UserData);
        }
        if (total == 15000) {
            statistics.time15000 = total_insertion_time;
            statistics.size15000 = sizeof(table) + table.getSize() * sizeof(UserData);
        }
        if (total == 20000) {
            statistics.time20000 = total_insertion_time;
            statistics.size20000 = sizeof(table) + table.getSize() * sizeof(UserData);
        }
    }

    auto end_total = std::chrono::high_resolution_clock::now(); // Fin del tiempo total
    std::chrono::duration<double> elapsed_total = end_total - start_total;

    // Calcula el tiempo promedio de inserción y cierra el archivo
    statistics.average_put = total_insertion_time / total;
    file.close();

    // Retorna las estadísticas calculadas
    return statistics;
}

#endif // READCSV_H
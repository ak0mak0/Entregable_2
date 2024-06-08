#ifndef AVARAGEPUTID_H
#define AVARAGEPUTID_H
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "stats.h"
#include "readCSV.h"

template <typename HashTable>
void calculateAveragePutID(HashTable &user_id_table, const std::string &table_name) {
    std::ofstream outputFile("/home/ak0mak0/Escritorio/Entregable_2/experiment_put_results/" + table_name + ".csv", std::ios_base::app);

    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
        return;
    }

    // Check if the file is empty to write the header
    std::ifstream inputFile("/home/ak0mak0/Escritorio/Entregable_2/experiment_put_results/" + table_name + ".csv");
    if (inputFile.peek() == std::ifstream::traits_type::eof()) {
        outputFile << "cant_experimentos;dataset;estructura_de_datos;cantidad_consultas;tiempo_ejecucion_promedio;tamaño_estructura_de_dato;desviacion_estandar\n";
    }

    stats average_stats = {};
    std::string set = "user_id;";
    std::vector<double> times;

    for (int i = 0; i < 20; ++i) {
        user_id_table.clear();
        stats current_stats = readCSV(user_id_table, 1);

        average_stats.size1000 += current_stats.size1000;
        average_stats.size5000 += current_stats.size5000;
        average_stats.size10000 += current_stats.size10000;
        average_stats.size15000 += current_stats.size15000;
        average_stats.size20000 += current_stats.size20000;
        average_stats.time1000 += current_stats.time1000;
        average_stats.time5000 += current_stats.time5000;
        average_stats.time10000 += current_stats.time10000;
        average_stats.time15000 += current_stats.time15000;
        average_stats.time20000 += current_stats.time20000;
        average_stats.average_put += current_stats.average_put;

        // Add current_stats.time20000 to the times vector
        times.push_back(current_stats.time20000);
    }

    average_stats.size1000 /= 20;
    average_stats.size5000 /= 20;
    average_stats.size10000 /= 20;
    average_stats.size15000 /= 20;
    average_stats.size20000 /= 20;
    average_stats.time1000 /= 20;
    average_stats.time5000 /= 20;
    average_stats.time10000 /= 20;
    average_stats.time15000 /= 20;
    average_stats.time20000 /= 20;
    average_stats.average_put /= 20;

    // Calculate standard deviation
    double variance = 0.0;
    for (const auto &time : times) {
        variance += (time - average_stats.time20000) * (time - average_stats.time20000);
    }
    variance /= times.size();
    double standard_deviation = std::sqrt(variance);

    outputFile << "20;" + set + table_name + ";";
    outputFile << "1000;" << average_stats.time1000 << " ns;" << average_stats.size1000 << "\n";
    outputFile << "20;" + set + table_name + ";";
    outputFile << "5000;" << average_stats.time5000 << " ns;" << average_stats.size5000 << "\n";
    outputFile << "20;" + set + table_name + ";";
    outputFile << "10000;" << average_stats.time10000 << " ns;" << average_stats.size10000 << "\n";
    outputFile << "20;" + set + table_name + ";";
    outputFile << "15000;" << average_stats.time15000 << " ns;" << average_stats.size15000 << "\n";
    outputFile << "20;" + set + table_name + ";";
    outputFile << "20000;" << average_stats.time20000 << " ns;" << average_stats.size20000 << ";" << standard_deviation << "\n";

    outputFile.close();
}

#endif // AVARAGEPUTID_H
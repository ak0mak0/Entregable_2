#ifndef AVARAGEGETNOTID_H
#define AVARAGEGETNOTID_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <random>
#include <unordered_set>
#include <sstream>
#include <filesystem>
#include <numeric>
#include <chrono>
#include "stats.h"
#include "readCSV.h"
#include "user_data.h"
#include <chrono>

#include <vector>

std::vector<int> generateNumbers() {
    std::vector<int> numbers;
    int current_number = 1000000;

    for (int i = 0; i < 98; ++i) {
        numbers.push_back(current_number);
        current_number += 10000;
    }

    return numbers;
}

template <typename HashTable>
void calculateAverageGetNotID(HashTable &user_id_table, const std::string &table_name) {
    std::ofstream outputFile("/home/ak0mak0/Escritorio/Entregable_2/experiment_not_results/" + table_name + ".csv", std::ios_base::app);

    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
        return;
    }

    // Check if the file is empty to write the header
    std::ifstream inputFile("/home/ak0mak0/Escritorio/Entregable_2/experiment_not_results/" + table_name + ".csv");
    if (inputFile.peek() == std::ifstream::traits_type::eof()) {
        outputFile << "cant_experimentos;dataset;estructura_de_datos;valor_consulta;tiempo;tiempo_promedio;desviacion_estandar\n";
    }

    std::vector<int> numbers = generateNumbers();
    std::vector<double> times; // Vector para almacenar los tiempos individuales

    // Realizar las consultas y almacenar los tiempos
    for (size_t i = 0; i < numbers.size(); ++i) {
        UserData data;
        auto start = std::chrono::high_resolution_clock::now();
        user_id_table.get(std::to_string(numbers[i]), data);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::nano> elapsed = end - start;
        times.push_back(elapsed.count());
        
        // Calcular el promedio hasta el momento actual
        double sum = 0.0;
        for (size_t j = 0; j <= i; ++j) {
            sum += times[j];
        }
        double average_time = sum / (i + 1);

        // Calcular la desviación estándar hasta el momento actual
        double sum_of_squared_differences = 0.0;
        for (size_t j = 0; j <= i; ++j) {
            sum_of_squared_differences += (times[j] - average_time) * (times[j] - average_time);
        }
        double standard_deviation = std::sqrt(sum_of_squared_differences / (i));

        // Escribir los resultados en el archivo
        outputFile << "1000;user_id;" << table_name << ";" << numbers[i] << ";" << times[i] << ";" << average_time << ";" << standard_deviation << "\n";
    }

    outputFile.close();

}

#endif // AVARAGEGETNOTID_H
#ifndef AVARAGEGETNAME_H
#define AVARAGEGETID_H

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

// Función para obtener 1000 nombres de usuario aleatorios desde un archivo CSV
std::vector<std::string> getRandomUserNames() {
    std::ifstream file("/home/ak0mak0/Escritorio/Entregable_2/Complements/universities_followers.csv");
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return {};
    }

    std::vector<std::string> user_names;
    std::string line;

    // Leer la primera línea del archivo (cabecera)
    std::getline(file, line);

    // Leer el archivo CSV y almacenar los user_name en un vector
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string university, user_id, user_name, number_tweets, friends_count, followers_count, created_at;
        
        // Extraer los campos
        if (std::getline(ss, university, ',') &&
            std::getline(ss, user_id, ',') &&
            std::getline(ss, user_name, ',') &&
            std::getline(ss, number_tweets, ',') &&
            std::getline(ss, friends_count, ',') &&
            std::getline(ss, followers_count, ',') &&
            std::getline(ss, created_at, ',')) {
            
            user_names.push_back(user_name);
        }
    }

    file.close();

    if (user_names.size() < 9999) {
        std::cerr << "El archivo no contiene suficientes nombres de usuario." << std::endl;
        return {};
    }

    // Seleccionar aleatoriamente 1000 user_name diferentes
    std::unordered_set<int> selected_indices;
    std::vector<std::string> random_user_names;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, user_names.size() - 1);

    while (random_user_names.size() < 100) {
        int index = dis(gen);
        if (selected_indices.find(index) == selected_indices.end()) {
            selected_indices.insert(index);
            random_user_names.push_back(user_names[index]);
        }
    }

    return random_user_names;
}


template <typename HashTable>
void calculateAverageGetName(HashTable &user_id_table, const std::string &table_name) {
    std::ofstream outputFile("/home/ak0mak0/Escritorio/Entregable_2/experiment_get_results/" + table_name + ".csv", std::ios_base::app);

    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
        return;
    }

    // Check if the file is empty to write the header
    std::ifstream inputFile("/home/ak0mak0/Escritorio/Entregable_2/experiment_get_results/" + table_name + ".csv");
    if (inputFile.peek() == std::ifstream::traits_type::eof()) {
        outputFile << "cant_experimentos;dataset;estructura_de_datos;valor_consulta;tiempo;tiempo_promedio;desviacion_estandar\n";
    }

    std::vector<std::string> random_user_ids = getRandomUserNames();
    std::vector<double> times; // Vector para almacenar los tiempos individuales

    // Realizar las consultas y almacenar los tiempos
    for (size_t i = 0; i < random_user_ids.size(); ++i) {
        UserData data;
        auto start = std::chrono::high_resolution_clock::now();
        user_id_table.get(random_user_ids[i], data);
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
        outputFile << "10000;user_name;" << table_name << ";" << random_user_ids[i] << ";" << times[i] << ";" << average_time << ";" << standard_deviation << "\n";
    }

    outputFile.close();
}


#endif // AVARAGEGETNAME_H
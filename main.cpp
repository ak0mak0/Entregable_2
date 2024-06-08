#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <random>
#include <unordered_set>
#include <dirent.h>

#include "HashTables/linear_probing_name.h"
#include "HashTables/quadratic_proving_name.h"
#include "HashTables/double_hashing_name.h"
#include "HashTables/separate_chaining_name.h"
#include "HashTables/linear_probing_id.h"
#include "HashTables/quadratic_proving_id.h"
#include "HashTables/double_hashing_id.h"
#include "HashTables/separate_chaining_id.h"
#include "HashTables/unordered_map.h"

#include "Complements/test_put_id.h"
#include "Complements/test_put_name.h"
#include "Complements/test_get_id.h"
#include "Complements/test_get_name.h"
#include "Complements/test_get_not_id.h"
#include "Complements/test_get_not_name.h"

void clearDirectory(const std::string& directory_path) {
    DIR* dir = opendir(directory_path.c_str());
    if (dir != nullptr) {
        dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            std::string filename = entry->d_name;
            if (filename != "." && filename != "..") {
                std::string filepath = directory_path + "/" + filename;
                if (remove(filepath.c_str()) != 0) {
                    std::cerr << "Error al eliminar el archivo: " << filepath << std::endl;
                }
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Error al abrir el directorio: " << directory_path << std::endl;
    }
}

void clearAll() {
    std::string directories[] = {
        "/home/ak0mak0/Escritorio/Entregable_2/experiment_get_results/",
        "/home/ak0mak0/Escritorio/Entregable_2/experiment_put_results/",
        "/home/ak0mak0/Escritorio/Entregable_2/experiment_not_results/"
    };

    for (const auto& directory : directories) {
        clearDirectory(directory);
    }
}

int main() {
    clearAll();

    // Creación de instancias de las diferentes implementaciones de tablas hash
    SeparateChainingID sc1(27367);
    SeparateChainingName sc2(27367);
    calculateAveragePutID(sc1, "separate_chaining");
    calculateAverageGetID(sc1, "separate_chaining");
    calculateAverageGetNotID(sc1, "separate_chaining");
    calculateAveragePutName(sc2, "separate_chaining");
    calculateAverageGetName(sc2, "separate_chaining");
    calculateAverageGetNotName(sc2, "separate_chaining");
    

    LinearProbingID lp1(27367);
    LinearProbingName lp2(27367);
    calculateAveragePutID(lp1, "linear_probing");
    calculateAverageGetID(lp1, "linear_probing");
    calculateAverageGetNotID(lp1, "linear_probing");
    calculateAveragePutName(lp2, "linear_probing");
    calculateAverageGetName(lp2, "linear_probing");
    calculateAverageGetNotName(lp2, "linear_probing");

    QuadraticProbingID qp1(27367);
    QuadraticProbingName qp2(27367);
    calculateAveragePutID(qp1, "quadratic_probing");
    calculateAverageGetID(qp1, "quadratic_probing");
    calculateAverageGetNotID(qp1, "quadratic_probing");
    calculateAveragePutName(qp2, "quadratic_probing");
    calculateAverageGetName(qp2, "quadratic_probing");
    calculateAverageGetNotName(qp2, "quadratic_probing");

    DoubleHashingID dh1(27367);
    DoubleHashingName dh2(27367);
    calculateAveragePutID(dh1, "double_hashing");
    calculateAverageGetID(dh1, "double_hashing");
    calculateAverageGetNotID(dh1, "double_hashing");
    calculateAveragePutName(dh2, "double_hashing");
    calculateAverageGetName(dh2, "double_hashing");
    calculateAverageGetNotName(dh2, "double_hashing");

    UnorderedMap um1;
    
    UnorderedMap um2;
    calculateAveragePutID(um1, "unordered_map");
    calculateAverageGetID(um1, "unordered_map");
    calculateAverageGetNotID(um1, "unordered_map");
    calculateAveragePutName(um2, "unordered_map");
    calculateAverageGetName(um2, "unordered_map"); 
    calculateAverageGetNotName(um2, "unordered_map"); 
}


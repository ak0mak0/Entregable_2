#ifndef SEPARATECHAININGID_H
#define SEPARATECHAININGID_H

#include "../Complements/user_data.h"
#include "../Complements/hash_table.h"
#include "../Complements/my_pair.h"
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

// Implementación de la tabla hash con hashing abierto (encadenamiento)
class SeparateChainingID : public HashTable{
private:
    std::vector<std::list<MyPair>> table;

    // Función hash para dispersar un userID (string que almacena un valor entero)
    int hashFunction(const std::string& userID) const{
        size_t hashValue = 0;
        for (char c : userID) {
            hashValue = 31 * hashValue + c; // Utilizamos una versión simple del algoritmo de Horner
        }
        return hashValue % table.size();
    }

public:
    // Constructor para inicializar la tabla con un tamaño dado y seleccionar la función hash
    SeparateChainingID(int size) : table(size) {}

    // Inserta un elemento en la tabla hash, falta manejar caso de misma key
    bool put(const std::string &key, const UserData &data) {
        int index = hashFunction(key);
        auto &lista = table[index];
        
        // Busca si la clave ya existe y actualiza el valor
        for (auto &item : lista) {
            if (item.key == key) {
                item.data = data;
                return true;
            }
        }
        
        // Si la clave no existe, inserta un nuevo par clave-valor
        lista.push_back({key, data});
        return true;
    }

    // Encuentra un elemento en la tabla hash
    bool get(const std::string &key, UserData &data) const{
        int index = hashFunction(key);
        for (auto &par : table[index]) {
            if (par.key == key) {
                data = par.data;
                return true;
            }
        }
        return false;
    }

    // Elimina un elemento de la tabla hash
    bool remove(const std::string &key) {
        int index = hashFunction(key);
        auto &lista = table[index];
        for (auto it = lista.begin(); it != lista.end(); ++it) {
            if (it->key == key) {
                lista.erase(it);
                return true;
            }
        }
        return false;
    }

    // Obtiene el número de elementos en la tabla hash
    int getSize() const {
        int count = 0;
        for (const std::list<MyPair> &lista : table) {
            count += lista.size();
        }
        return count;
    }
    
    // Verifica si la tabla hash está vacía
    bool empty() const {
        for (const std::list<MyPair> &lista : table) {
            if (!lista.empty()) {
                return false;
            }
        }
        return true;
    }

    // Limpia la tabla hash
    void clear() {
        for (std::list<MyPair> &lista : table) {
            lista.clear();
        }
    }
};


#endif // SEPARATECHAININGID_H

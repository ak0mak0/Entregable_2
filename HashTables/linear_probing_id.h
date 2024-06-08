#ifndef LINEARPROBINGID_H
#define LINEARPROBINGID_H

#include "../Complements/user_data.h"
#include "../Complements/hash_table.h"
#include <vector>
#include <string>

// Implementación de la tabla hash con hashing cerrado (Sondeo lineal)
class LinearProbingID : public HashTable{
private:
    struct Slot {
        std::string key; // Clave del elemento
        UserData data; // Datos asociados a la clave
        bool used; // Bandera para indicar si la ranura está ocupada
        bool deleted; // Bandera para indicar si el elemento ha sido eliminado

        Slot() : used(false), deleted(false) {} // Constructor por defecto
    };

    std::vector<Slot> table; // Tabla hash
    int capacity; // Capacidad de la tabla
    int size; // Tamaño actual de la tabla

    // Función hash para dispersar un userID (string que almacena un valor entero)
    int hashFunction(const std::string& userID) const{
        size_t hashValue = 0;
        for (char c : userID) {
            hashValue = 31 * hashValue + c; // Utilizamos una versión simple del algoritmo de Horner
        }
        return hashValue % capacity;
    }
    // Función de rehashing para aumentar el tamaño de la tabla y reinsertar elementos
    void rehash() {
        std::vector<Slot> oldTable = std::move(table); // Movemos la tabla antigua para evitar copias
        capacity *= 2;
        table = std::vector<Slot>(capacity);
        size = 0;

        for (const Slot &slot : oldTable) {
            if (slot.used && !slot.deleted) {
                put(slot.key, slot.data); // Reinsertamos los elementos
            }
        }
    }

public:
    LinearProbingID
(int capacity) : table(capacity), capacity(capacity), size(0) {}
    
    // Inserta un elemento en la tabla
    bool put(const std::string &key, const UserData &data) {
        if (4 * size >= 3 * capacity) {
            rehash();
        }

        int index = hashFunction(key);
        int originalIndex = index;
        bool foundDeleted = false;
        int deletedIndex = -1;

        while (true) {
            if (!table[index].used) {
                if (!foundDeleted) {
                    table[index].key = key;
                    table[index].data = data;
                    table[index].used = true;
                    size++;
                } else {
                    table[deletedIndex].key = key;
                    table[deletedIndex].data = data;
                    table[deletedIndex].used = true;
                    table[deletedIndex].deleted = false;
                }
                return true;
            } else if (table[index].deleted && !foundDeleted) {
                foundDeleted = true;
                deletedIndex = index;
            } else if (table[index].key == key) {
                table[index].data = data;
                return true;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) {
                break;
            }
        }
        return false;
    }
    
    // Obtiene un elemento de la tabla dado su clave
    bool get(const std::string &key, UserData &data) const {
        int index = hashFunction(key);
        int originalIndex = index;

        while (true) {
            const Slot& slot = table[index]; // Usar una referencia constante para el slot actual
            if (slot.used && slot.key == key && !slot.deleted) {
                data = slot.data;
                return true;
            }
            if (!slot.used && !slot.deleted) {
                return false; // Terminar si encontramos un slot vacío que no ha sido borrado
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) {
                break;
            }
        }
        return false;
    }
    
    // Elimina un elemento de la tabla dado su clave
    bool remove(const std::string &key) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (true) {
            if (table[index].used && table[index].key == key && !table[index].deleted) {
                table[index].deleted = true;
                size--;
                return true;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) {
                break;
            }
        }

        return false;
    }
    
    // Obtiene el tamaño actual de la tabla
    int getSize() const { return size; }
    
    int getCapacity() const { return capacity; }
    
    // Verifica si la tabla está vacía    
    bool empty() const { return size == 0; }

    // Limpia la tabla
    void clear() {
        for (Slot &slot : table) {
            slot.used = false;
            slot.deleted = false;
        }
        size = 0;
    }
};

#endif // LINEARPROBINGID_H

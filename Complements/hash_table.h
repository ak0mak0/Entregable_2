#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "user_data.h"
#include <string>

// Interfaz para una tabla hash genérica
class HashTable {
public:
    // Método virtual puro para insertar un elemento en la tabla hash
    virtual bool put(const std::string &key, const UserData &data) = 0;

    // Método virtual puro para obtener un elemento de la tabla hash
    virtual bool get(const std::string &key, UserData &data) const = 0;

    // Método virtual puro para eliminar un elemento de la tabla hash
    virtual bool remove(const std::string &key) = 0;

    // Método virtual puro para obtener el tamaño de la tabla hash
    virtual int getSize() const = 0;

    // Método virtual puro para verificar si la tabla hash está vacía
    virtual bool empty() const = 0;

    // Método virtual puro para limpiar la tabla hash
    virtual void clear() = 0;

    // Destructor virtual para la interfaz de la tabla hash
    virtual ~HashTable() = default;
};

#endif // HASHTABLE_H


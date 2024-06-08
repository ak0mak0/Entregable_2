#ifndef MYPAIR_H
#define MYPAIR_H

#include "../Complements/user_data.h"
#include <string>

// Definición de una estructura de par que contiene una clave (string) y los datos del usuario (UserData)
struct MyPair {
    std::string key; // Clave del par
    UserData data; // Datos del usuario asociados a la clave
};

#endif // MYPAIR_H
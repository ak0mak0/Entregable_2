#ifndef USERDATA_H
#define USERDATA_H

#include <string>

// Definición del struct para almacenar los datos de una fila
struct UserData {
    std::string university; // Nombre de la universidad
    std::string user_id; // Identificación del usuario
    std::string user_name; // Nombre del usuario
    int number_tweets; // Número de tweets
    int friends_count; // Cantidad de amigos
    int followers_count; // Cantidad de seguidores
    std::string created_at; // Fecha de creación

    // Constructor predeterminado
    UserData() : number_tweets(0), friends_count(0), followers_count(0) {}

    // Constructor para inicializar todos los campos
    UserData(const std::string &university, const std::string &user_id,
             const std::string &user_name, int tweets, int friends, int followers,
             const std::string &created_at)
        : university(university), user_id(user_id), user_name(user_name),
          number_tweets(tweets), friends_count(friends),
          followers_count(followers), created_at(created_at) {}
};

#endif // USERDATA_H

#include <unordered_map>
#include "../Complements/user_data.h"

class UnorderedMap {
private:
    std::unordered_map<std::string, UserData> map;

public:

    // Inserta un elemento en la tabla
    bool put(const std::string &key, const UserData &data) {
        map[key] = data;
        return true;
    }

    // Obtiene un elemento de la tabla dado su clave
    bool get(const std::string &key, UserData &data) const {
        auto it = map.find(key);
        if (it != map.end()) {
            data = it->second;
            return true;
        }
        return false;
    }

    // Elimina un elemento de la tabla dado su clave
    bool remove(const std::string &key) {
        return map.erase(key) > 0;
    }

    // Obtiene el tamaño actual de la tabla
    int getSize() const {
        return map.size();
    }

    // Verifica si la tabla está vacía
    bool empty() const {
        return map.empty();
    }
    
    // Limpia la tabla
    void clear() {
        map.clear();
    }
};

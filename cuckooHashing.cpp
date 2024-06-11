// cuckooHashing.cpp
#include "cuckooHashing.h"
#include <functional> // Para std::hash

cuckooHashing::cuckooHashing(size_t size)
    : table1(size, -1), table2(size, -1) {
}

size_t cuckooHashing::hash1(const uint64_t& key) const {
    return std::hash<uint64_t>{}(key) % table1.size();
}

size_t cuckooHashing::hash2(const uint64_t& key) const {
    return (std::hash<uint64_t>{}(key) / table1.size()) % table2.size();
}

bool cuckooHashing::search(const uint64_t& key) const {
    size_t pos1 = hash1(key);
    if (table1[pos1] == key) {
        return true;
    }
    size_t pos2 = hash2(key);
    return table2[pos2] == key;
}

void cuckooHashing::insert(const uint64_t& key) {
    size_t pos1 = hash1(key);
    if (table1[pos1] == -1) {
        table1[pos1] = key;
        return;
    }
    size_t pos2 = hash2(key);
    if (table2[pos2] == -1) {
        table2[pos2] = key;
        return;
    }
    // Reubicación de elementos en caso de colisión
    // Esto es una simplificación. En un escenario real, deberías manejar los ciclos y reubicaciones.
}
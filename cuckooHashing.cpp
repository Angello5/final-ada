#include "cucckoHashing.h"
#include <iostream>
#include <vector>

cuckooHashing::cuckooHashing(int size) : size(size){
    table1.resize(size, "");
    table2.resize(size, "");
}

int CuckooHashing::hash1(int key) {
    return key % size;
}

int CuckooHashing::hash2(int key) {
    return (key / size) % size;
}

void CuckooHashing::insert(const std::string& key) {
    int pos1 = hash1(std::stoi(key));
    if (table1[pos1].empty()) {
        table1[pos1] = key;
        return;
    }

    std::string curr = key;
    if (table1[pos1] != key) {
        std::swap(curr, table1[pos1]);
    }

    int pos2 = hash2(std::stoi(curr));
    if (table2[pos2].empty()) {
        table2[pos2] = curr;
        return;
    } else if (table2[pos2] != curr) {
        std::swap(curr, table2[pos2]);
        insert(curr); // recursive re-insert
    }
}

bool CuckooHashing::search(const std::string& key) {
    int pos1 = hash1(std::stoi(key));
    if (table1[pos1] == key) return true;
    int pos2 = hash2(std::stoi(key));
    if (table2[pos2] == key) return true;
    return false;
}
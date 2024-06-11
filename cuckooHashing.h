// cuckooHashing.h
#ifndef CUCKOOHASHING_H
#define CUCKOOHASHING_H


#include <vector>
#include <cstdint>  // Para usar uint64_t

using namespace std;


class cuckooHashing {
public:
    cuckooHashing(size_t size);
    bool search(const uint64_t& key) const;
    void insert(const uint64_t& key);

private:
    size_t hash1(const uint64_t& key) const;
    size_t hash2(const uint64_t& key) const;
    vector<int64_t> table1;
    vector<int64_t> table2;
};

#endif 
#ifndef CUCKOOHASHING_H
#define CUCKOOHASHING_H
#include <vector>
#include <string>

using namespace std;

class cuckooHashing
{
private:
    vector<string> table1, table2;
    int size;
    int hash1(int key);
    int hash2(int key);
    void rehash();
    
public:
    cuckooHashing(int size);
    void insert(string& key);
    void search(string& key);
};


#endif
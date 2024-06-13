#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;
class HashTable {
public:
    HashTable(size_t size);
    bool insert(string& key, string& value);
    bool get(string& key, string& value);
    bool remove(string& key);
    void print();
    void resize(size_t);

private:
    std::vector<pair<string, string>*> table;
    size_t size;
    size_t count;
    size_t hashFunction(string& key);
};

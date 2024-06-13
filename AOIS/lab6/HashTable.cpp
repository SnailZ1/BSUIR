#include "HashTable.h"

HashTable::HashTable(size_t size) : table(size, nullptr), size(size), count(0) {}

bool HashTable::insert(string& key, string& value) {
    if (count >= size) {
        resize(size * 1.5);
    }

    size_t index = hashFunction(key);
    size_t i = 0;

    while (table[index] != nullptr) {
        if (table[index]->first == key) {
            table[index]->second = value;
            return true;
        }
        index = (index + i * i) % size;
        ++i;
    }

    table[index] = new pair<string, string>(key, value);
    ++count;
    return true;
}

bool HashTable::get(string& key, string& value) {
    size_t index = hashFunction(key);
    size_t i = 0;

    while (table[index] != nullptr) {
        if (table[index]->first == key) {
            value = table[index]->second;
            return true;
        }
        index = (index + i * i) % size;
        ++i;
    }

    return false;
}

bool HashTable::remove(string& key) {
    size_t index = hashFunction(key);
    size_t i = 0;

    while (table[index] != nullptr) {
        if (table[index]->first == key) {
            delete table[index];
            table[index] = nullptr;
            --count;
            return true;
        }
        index = (index + i * i) % size;
        ++i;
    }

    return false;
}

void HashTable::print() {
    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i] != nullptr) {
            cout << "Cell " << i << ": " << table[i]->first << " : " << table[i]->second << endl;
        }
        else {
            cout << "Cell " << i << ": Empty" << endl;
        }
    }
}

void HashTable::resize(size_t newSize) {
    vector<pair<string, string>*> newTable(newSize, nullptr);
    for (const auto& item : table) {
        if (item != nullptr) {
            size_t index = hashFunction(item->first);
            size_t i = 0;
            while (newTable[index] != nullptr) {
                index = (index + i * i) % newSize;
                ++i;
            }
            newTable[index] = item;
        }
    }
    table = std::move(newTable);
    size = newSize;
}

size_t HashTable::hashFunction(string& key) {
    size_t hash = 0;
    for (char c : key) {
        hash = hash + c;
    }
    return hash % size;
}
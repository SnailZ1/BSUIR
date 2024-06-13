#include <iostream>
#include "HashTable.h"


int main() {
    HashTable hashTable(10);
    int choice;
    string key, value;

    while (true) {
        cout << "1. Insert" << endl;
        cout << "2. Get" << endl;
        cout << "3. Remove" << endl;
        cout << "4. Print" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter key: ";
            cin >> key;
            cout << "Enter value: ";
            cin >> value;
            if (hashTable.insert(key, value)) {
                cout << "Inserted successfully" << endl;
            }
            else {
                cout << "Insertion failed" << endl;
            }
            break;

        case 2:
            cout << "Enter key: ";
            cin >> key;
            if (hashTable.get(key, value)) {
                cout << "Value: " << value << endl;
            }
            else {
                cout << "Key not found" << endl;
            }
            break;

        case 3:
            cout << "Enter key: ";
            cin >> key;
            if (hashTable.remove(key)) {
                cout << "Removed successfully" << endl;
            }
            else {
                cout << "Key not found" << endl;
            }
            break;

        case 4:
            hashTable.print();
            break;

        case 5:
            return 0;
            
        default:
            cout << "Invalid choice" << endl;
        }
    }

    return 0;
}

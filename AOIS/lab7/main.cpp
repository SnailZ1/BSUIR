#include "Matrix.h"
#include <iostream>

using namespace std;

int main() {
    vector<vector<bool>> data = {
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    Matrix mat(data);
    vector<bool> word;
    vector<bool> adres;
    mat.print();
    int choice;
    int row;
    int column;
    bool value;
    int index;
    string func;
    vector<bool> v;
    vector<int> interval;
    while (true) {
        cout << "1. Change element" << endl;
        cout << "2. Get word" << endl;
        cout << "3. Print matrix" << endl;
        cout << "4. Functions" << endl;
        cout << "5. SummFields" << endl;
        cout << "6. SearchInterval" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter row: ";
            cin >> row;
            cout << "Enter column: ";
            cin >> column;
            cout << "Enter value: ";
            cin >> value;
            mat.setElement(row, column, value);
            break;

        case 2:
            cout << "Enter index: ";
            cin >> index;
            word = mat.getWord(index);
            mat.printWord(word);
            adres = mat.getAdres(index);
            mat.printAdres(adres);
            break;

        case 3:
            mat.print();
            break;

        case 4:
            cout << "Enter first word: ";
            cin >> row;
            cout << "Enter second word: ";
            cin >> column;
            cout << "Enter third word: ";
            cin >> index;
            cout << "Enter function(f7, f8 , f2, f13) ";
            cin >> func;
            mat.replaceWord(row, column, index, func);
            break;

        case 5:
            cout << "Enter value:";
            cin >> value;
            v.push_back(value);
            cin >> value;
            v.push_back(value);
            cin >> value;
            v.push_back(value);
            mat.summFields(v);
            break;

        case 6:
            cout << "Enter interval: ";
            cout << "Enter first: ";
            cin >> row;
            cout << "Enter second: ";
            cin >> column;
            interval = mat.searchInterval(row, column);
            for (int i = 0; i < interval.size(); i++) {
                cout << interval[i] << " ";
                mat.printWord(mat.getWord(interval[i]));
                mat.printAdres(mat.getAdres(interval[i]));
                cout << endl;
            }
            break;

        case 7:
            return 0;

        default:
            cout << "Invalid choice" << endl;
        }
    }

    return 0;
}
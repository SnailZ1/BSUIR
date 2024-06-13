#include <vector>
#include <iostream>

using namespace std;

class Matrix {
public:
    Matrix(vector<vector<bool>> data);
    void setElement(int row, int col, bool value);
    vector<bool> getWord(int index);
    vector<bool> getAdres(int index);
    void printWord(vector<bool>);
    void printAdres(vector<bool>);
    vector<vector<bool>> replaceWord(int num1, int num2, int num3, string function);
    vector<vector<bool>> summFields(vector<bool>);
    int binaryToDecimal(vector<bool> binary);
    vector<int> searchInterval(int, int);
    void print();

private:
    vector<vector<bool>> data;
};
#pragma once

#include "FixedPoint.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class IntNum {
private:
    int num;
    vector<bool> directCode;
    vector<bool> invertCode;
    vector<bool> additionalCode;
    int bitsCount = 8;
public:
    int getBitsCount();
    void setBitsCount(int);

    IntNum(int);
    void printValue();

    bool compareBinary(string first, string second);
    int binaryToDecimal(string directCode);
    string decimalToBinary(int num);

    IntNum& operator =(const IntNum& a);
    IntNum operator +(const IntNum& a);
    IntNum operator *(const IntNum& a);
    FixedPoint operator /(const IntNum& a);
};

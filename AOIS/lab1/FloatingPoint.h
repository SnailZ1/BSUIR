#pragma once

#include <iostream>
#include <vector>

using namespace std;

class FloatingData {
private:
    float value;
    bool sign;
    int exponent;
    vector<bool> mantissa;
    vector<bool> exponentBits;
public:
    FloatingData(float);
    void displayValue();

    FloatingData& operator =(const FloatingData& a);
    FloatingData operator +(const FloatingData& a);
};

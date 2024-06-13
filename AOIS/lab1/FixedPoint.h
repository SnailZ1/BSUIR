#pragma once

#include <iostream>
#include <vector>

using namespace std;

class FixedPoint {
private:
    vector<bool> integ;
    vector<bool> remain;
public:
    friend class IntNum;
    void print();
    FixedPoint& operator =(const FixedPoint& a);
};

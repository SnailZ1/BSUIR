#include "FixedPoint.h"

void FixedPoint::print() {
    cout << "FixedPoint: ";
    cout << "[" << integ[0] << "] ";
    for (int i = 1; i < integ.size(); i++) {
        cout << integ[i] << " ";
    }
    cout << ".";
    for (int i = 0; i < remain.size(); i++) {
        cout << remain[i] << " ";
    }
    cout << endl;
}

FixedPoint& FixedPoint::operator =(const FixedPoint& a) {
    integ = a.integ;
    remain = a.remain;
    return *this;
}

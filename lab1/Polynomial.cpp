#include "Polynomial.h"
#include <vector>
#include <iostream>

using namespace std;

Polynom::Polynom(int deg, vector<double> coef) : degree(deg) {
    coefficients = coef;
}

Polynom::Polynom() : degree(0) {}

int Polynom::getDegree() const{
    return degree;
}

double Polynom::operator [](int ind) const{
    return coefficients[ind];
}

double& Polynom::operator [](int ind) {
    return coefficients[ind-1];
}

double Polynom::operator ()(int x) {
    double res = 0;
    for (int i = 0, j = degree - 1; i < degree; i++, j--) {
        res += coefficients[i] * pow(x, j);
    }
    return res;
}

void Polynom::print() {
    for (int i = 0; i < degree; i++) {
        cout << coefficients[i] << endl;
    }
}

Polynom Polynom::operator+(const Polynom& sec) {
    int newDegree = max(degree, sec.degree);
    vector<double> newCoeffs(newDegree, 0);
    for (int i = 0; i < newDegree; i++) {
        if (i < degree) {
            newCoeffs[i] += coefficients[i];
        }
        if (i < sec.degree) {
            newCoeffs[i] += sec.coefficients[i];
        }
    }
    return Polynom(newDegree, newCoeffs);
}

Polynom& Polynom::operator+=(const Polynom& sec) {
    *this = *this + sec;
    return *this;
}

Polynom Polynom::operator-(const Polynom& sec) {
    int newDegree = max(degree, sec.degree);
    vector<double> newCoeffs(newDegree, 0);
    for (int i = 0; i < newDegree; i++) {
        if (i < degree) {
            newCoeffs[i] += coefficients[i];
        }
        if (i < sec.degree) {
            newCoeffs[i] -= sec.coefficients[i];
        }
    }
    return Polynom(newDegree, newCoeffs);
}

Polynom& Polynom::operator-=(const Polynom& sec) {
    *this = *this - sec;
    return *this;
}

Polynom Polynom::operator*(const Polynom& sec) {
    int newDegree = degree + sec.degree - 1;
    vector<double> newCoeffs(newDegree, 0);
    for (int i = 0; i < degree; i++) {
        for (int j = 0; j < sec.degree; j++) {
            newCoeffs[i + j] += coefficients[i] * sec.coefficients[j];
        }
    }
    return Polynom(newDegree, newCoeffs);
}

Polynom& Polynom::operator*=(const Polynom& sec) {
    *this = *this * sec;
    return *this;
}

Polynom Polynom::operator/(const Polynom& sec) {
    int resultDegree = degree - sec.degree + 1;
    vector<double> resultCoeffs(resultDegree, 0);
    vector<double> temp(coefficients);

    for (int i = 0; i < resultDegree; ++i) {
        resultCoeffs[i] = temp[i] / sec.coefficients[0];
        double factor = resultCoeffs[i];
        for (int j = 0; j < sec.degree; ++j) {
            temp[i + j] -= factor * sec.coefficients[j];
        }
    }
    Polynom result(resultDegree, resultCoeffs);
    return result;
}


Polynom& Polynom::operator/=(const Polynom& sec) {
    *this = *this / sec;
    return *this;
}

bool Polynom::operator==(const Polynom& sec) const {
    if (degree == sec.degree && coefficients == sec.coefficients)
        return true;
    return false;
}
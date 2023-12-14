#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Polynom {
private:
	int degree;
	vector<double> coefficients;

public:
	Polynom(int deg, vector<double> coef);
	Polynom();
	int getDegree() const;
	double operator [](int ind) const;
	double& operator [](int ind);
	double operator ()(int x);
	void print();
	Polynom operator+(const Polynom& sec);
	Polynom& operator+=(const Polynom& sec);
	Polynom operator-(const Polynom& sec);
	Polynom& operator-=(const Polynom& sec);
	Polynom operator*(const Polynom& sec);
	Polynom& operator*=(const Polynom& sec);
	Polynom operator/(const Polynom& sec);
	Polynom& operator/=(const Polynom& sec);
	bool operator==(const Polynom& sec) const;
};
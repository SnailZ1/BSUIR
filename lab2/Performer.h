#pragma once
#include <iostream>
#include <string>

using namespace std;

class Perfomer {
private:
	string name;
	int yearsActive;
public:
	void setName(string);
	void setYearsActive(int);
	string getName();
	int getYearsActive();
	Perfomer(string, int);
};
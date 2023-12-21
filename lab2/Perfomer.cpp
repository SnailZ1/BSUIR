#include "Performer.h"

void Perfomer::setName(string name) {
	this->name = name;
}

void Perfomer::setYearsActive(int yearsActive) {
	this->yearsActive = yearsActive;
}

string Perfomer::getName() {
	return name;
}
int Perfomer::getYearsActive() {
	return yearsActive;
}

Perfomer::Perfomer(string name, int yearsActive) : name(name), yearsActive(yearsActive) {

}
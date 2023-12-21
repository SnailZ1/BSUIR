#include "Concert.h"

void Concert::setLocation(string location) {
	this->location = location;
}

void Concert::setConcertTime(string concertTime) {
	this->concertTime = concertTime;
}

string Concert::getLocation() {
	return location;
}

string Concert::getConcertTime() {
	return concertTime;
}
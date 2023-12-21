#include "Music.h"

void Music::setPerfomer(string perfomer) {
	this->perfomer = perfomer;
}

string Music::getPerfomer() {
	return perfomer;
}

Music::Music(string title, double duration, int day, int month, int year, string perfomer) : AudioFile(title, duration, day, month, year), perfomer(perfomer) {

}

void Music::getInfo() {
	cout << this->getTitle() << " " << this->getDuration() << " " << this->getDate() << " " << perfomer << endl;
}
#include "AudioBook.h"

void AudioBook::setPerfomer(string perfomer) {
	this->perfomer = perfomer;
}

void AudioBook::setSize(int size) {
	this->size = size;
}

void AudioBook::setPart(int part) {
	this->part = part;
}

string AudioBook::getPerfomer() {
	return perfomer;
}

int AudioBook::getSize() {
	return size;
}

int AudioBook::getPart() {
	return part;
}

AudioBook::AudioBook(string title, double duration, int day, int month, int year, string perfomer, int size, int part) : AudioFile(title, duration, day, month, year), perfomer(perfomer), size(size), part(part) {

}

bool AudioBook::playPage(int page) {
	if (page >0 && page <=size) {
		return true;
	}
	else {
		throw runtime_error("Error");
	}
}
#include "Album.h"

int Album::sizeOfList() {
	return listMusic.size();
}

void Album::addMusic(Music* song) {
	listMusic.push_back(song);
}

void Album::removeMusic(int number) {
	listMusic.erase(listMusic.begin() + number - 1);
}

void Album::getInfo() {
	for (const auto& listMusic : listMusic) {
		listMusic->getInfo();
	}
}
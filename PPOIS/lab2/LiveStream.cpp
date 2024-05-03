#include "LiveStream.h"

void LiveStream::addMusic(Music* song) {
	listMusic.push_back(song);
}

void LiveStream::removeMusic(int number) {
	listMusic.erase(listMusic.begin() + number - 1);
}

void LiveStream::getInfo() {
	for (const auto& listMusic : listMusic) {
		listMusic->getInfo();
	}
}
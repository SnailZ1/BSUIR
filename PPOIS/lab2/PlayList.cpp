#include "PlayList.h"

void PlayList::addMusic(Music* song) {
	listMusic.push_back(song);
}

void PlayList::removeMusic(int number) {
	listMusic.erase(listMusic.begin() + number - 1);
}

void PlayList::getInfo() {
	for (const auto& listMusic : listMusic) {
		listMusic->getInfo();
	}
}
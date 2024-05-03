#include "User.h"

void User::setName(string name) {
	this->name = name;
}

string User::getName() {
	return name;
}

void User::addToLoveMusic(Music* song) {
	loveMusic.push_back(song);
}

void User::removeFromLoveMusic(int number) {
	loveMusic.erase(loveMusic.begin() + number - 1);
}

void User::checkLoveMusic() {
	for (const auto& loveMusic : loveMusic) {
		loveMusic->getInfo();
	}
}

string User::rate(int value) {
	string rating;
	if (value < 4) {
		return rating = "bad";
	}
	else if (value >= 4 && value < 8) {
		return rating = "normal";
	}
	else return rating = "good";
}

Music* User::findByTitle(const string& title) {
	for (const auto& loveMusic : loveMusic) {
		if (loveMusic->getTitle() == title) {
			return loveMusic;
		}
	}
	throw runtime_error("Error");
}

Music* User::findByPerfomer(const string& perfomer) {
	for (const auto& loveMusic : loveMusic) {
		if (loveMusic->getPerfomer() == perfomer) {
			return loveMusic;
		}
	}
	throw runtime_error("Error");
}

Music* User::findByDate(const string& date) {
	for (const auto& loveMusic : loveMusic) {
		if (loveMusic->getDate() == date) {
			return loveMusic;
		}
	}
	throw runtime_error("Error");
}
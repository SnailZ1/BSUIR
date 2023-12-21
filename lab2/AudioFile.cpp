#include "AudioFile.h"

void AudioFile::setTitle(string title) {
	this->title = title;
}

void AudioFile::setDuration(double duration) {
	this->duration = duration;
}

void AudioFile::setDate(int day,int month,int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

string AudioFile::getTitle() {
	return title;
}

double AudioFile::getDuration() {
	return duration;
}

string AudioFile::getDate() {
	string date;
	date = to_string(day) + "." + to_string(month) + "." + to_string(year);
	return date;
}

AudioFile::AudioFile(string title, double duration, int day, int month, int year) : title(title), duration(duration), day(day), month(month), year(year) {

}

bool AudioFile::play() {
	if (isPlaying == false) {
		isPlaying = true;
		return true;
	}
	else {
		throw runtime_error("Error");
	}
}

bool AudioFile::pause() {
	if (isPlaying == true) {
		isPlaying = false;
		return true;
	}
	else {
		throw runtime_error("Error");
	}
}

bool AudioFile::stop() {
	if (isPlaying == true) {
		isPlaying = false;
		return true;
	}
	else {
		throw runtime_error("Error");
	}
}

void AudioFile::getInfo() {
	cout << title << " " << duration << " " << this->getDate() << endl;
}
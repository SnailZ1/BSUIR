#pragma once
#include "AudioFile.h"

class AudioBook : public AudioFile {
private:
	string perfomer;
	int size;
	int part;
public:
	void setPerfomer(string);
	void setSize(int);
	void setPart(int);
	string getPerfomer();
	int getSize();
	int getPart();
	AudioBook(string, double, int, int, int, string, int, int);
	bool playPage(int);
};
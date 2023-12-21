#pragma once
#include "AudioFile.h"

class Music: public AudioFile {
private:
	string perfomer;
public:
	void setPerfomer(string);
	string getPerfomer();
	Music(string, double, int, int, int, string);
	void getInfo();
};
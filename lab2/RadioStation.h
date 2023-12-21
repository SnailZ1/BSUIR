#pragma once
#include "AudioFile.h"
#include <vector>

class RadioStation {
private:
	vector<AudioFile*> queue;
public:
	int sizeOfQueue();
	void addToQueue(AudioFile*);
	void removeFromQueue(int);
	void getInfo();
};
#pragma once
#include "Music.h"
#include <vector>

class Album {
private:
	vector<Music*> listMusic;
public:
	int sizeOfList();
	void addMusic(Music*);
	void removeMusic(int);
	void getInfo();
};
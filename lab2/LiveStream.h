#pragma once
#include "Music.h"
#include "PlayList.h"
#include <vector>

class LiveStream : PlayList {
private:
	vector<Music*> listMusic;
public:
	void addMusic(Music*);
	void removeMusic(int);
	void getInfo();
};
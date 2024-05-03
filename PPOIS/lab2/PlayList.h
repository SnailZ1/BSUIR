#pragma once
#include "Music.h"
#include "Album.h"
#include <vector>

class PlayList : public Album {
private:
	vector<Music*> listMusic;
public:
	void addMusic(Music*);
	void removeMusic(int);
	void getInfo();
};
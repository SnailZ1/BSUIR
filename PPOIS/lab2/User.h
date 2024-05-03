#pragma once
#include "Music.h"
#include <vector>

class User {
private:
	string name;
	vector<Music*> loveMusic;
public:
	void setName(string);
	string getName();
	void addToLoveMusic(Music*);
	void removeFromLoveMusic(int);
	void checkLoveMusic();
	string rate(int);
	Music* findByTitle(const string&);
	Music* findByPerfomer(const string&);
	Music* findByDate(const string&);
};
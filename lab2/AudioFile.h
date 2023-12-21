#pragma once
#include <iostream>
#include <string>

using namespace std;

class AudioFile {
private:
	string title;
	double duration;
	int day;
	int month;
	int year;
	bool isPlaying = false;
public:
	void setTitle(string);
	void setDuration(double);
	void setDate(int,int,int);
	string getTitle();
	double getDuration();
	string getDate();
	AudioFile(string, double, int, int, int);
	bool play();
	bool pause();
	bool stop();
	void getInfo();
};
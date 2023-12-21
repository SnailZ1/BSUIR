#pragma once
#include "LiveStream.h"

class Concert : public LiveStream {
private:
	string location;
	string concertTime;
public:
	void setLocation(string);
	void setConcertTime(string);
	string getLocation();
	string getConcertTime();
};
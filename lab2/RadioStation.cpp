#include "RadioStation.h"

int RadioStation::sizeOfQueue() {
	return queue.size();
}

void RadioStation::addToQueue(AudioFile* file) {
	queue.push_back(file);
}

void RadioStation::removeFromQueue(int number) {
	queue.erase(queue.begin() - number - 1);
}

void RadioStation::getInfo() {
	for (const auto& queue : queue) {
		queue->getInfo();
	}
}
/*
  ==============================================================================

    Semaphore.h
    Created: 13 May 2018 6:11:29pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
	Semaphore(int count = 0);
	void notify();
	void wait();

private:
	std::mutex _mutex;
	std::condition_variable _cv;
	int _count;
};
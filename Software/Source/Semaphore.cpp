/*
  ==============================================================================

    Semaphore.cpp
    Created: 13 May 2018 6:11:18pm
    Author:  Anthony

  ==============================================================================
*/

#include "Semaphore.hh"

Semaphore::Semaphore(int count)
{
	_count = count;
}

void Semaphore::notify()
{
	std::unique_lock<std::mutex> lock(_mutex);
	_count++;
	_cv.notify_one();
}

void Semaphore::wait()
{
	std::unique_lock<std::mutex> lock(_mutex);

	while (_count == 0)
	{
		_cv.wait(lock);
	}
	_count--;
}

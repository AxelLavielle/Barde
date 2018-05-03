/*
  ==============================================================================

    Tools.cpp
    Created: 22 Mar 2017 12:08:06pm
    Author:  Anthony

  ==============================================================================
*/

#include "Tools.hh"

void Tools::sleep(const unsigned int time)
{
#ifdef __linux__
	usleep(time * 1000);
#else
	Sleep(time);
#endif
}

void Tools::sleepActive(const unsigned int time)
{
#ifdef __linux__
	sleep(time); //Need to change that (use getTimeOfDay)
#else
	const DWORD startTime = GetTickCount();
	const DWORD stopTime = (startTime + time);

	while (GetTickCount() < stopTime);
#endif
}
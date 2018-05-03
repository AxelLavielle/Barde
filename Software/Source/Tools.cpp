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

//void Tools::sleepActive(const unsigned int time)
//{
//	SYSTEMTIME  system_time;
//
//	GetSystemTime(&system_time);
//	while ()
//	{
//
//	}
//}
/*
  ==============================================================================

    Tools.h
    Created: 22 Mar 2017 12:08:06pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef TOOLS_HH_INCLUDED
#define TOOLS_HH_INCLUDED

#ifdef __linux__
#include <unistd.h>
#else
#include <Windows.h>
#endif // DEBUG

class Tools
{
public:
	static void sleep(const unsigned int time);
	static void sleepActive(const unsigned int time);
};

#endif  // TOOLS_HH_INCLUDED

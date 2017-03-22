/*
  ==============================================================================

    Tools.cpp
    Created: 22 Mar 2017 12:08:06pm
    Author:  Anthony

  ==============================================================================
*/

#include "Tools.hh"

void Tools::sleep(unsigned int time)
{
#ifdef __linux__
	usleep(time);
#else
	Sleep(time);
#endif
}

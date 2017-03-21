/*
  ==============================================================================

    ASoundManager.h
    Created: 13 Mar 2017 1:42:09pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef ASOUNDMANAGER_HH_INCLUDED
#define ASOUNDMANAGER_HH_INCLUDED
#include "ISoundManager.hpp"

class ASoundManager : public ISoundManager
{
public:
	ASoundManager();
	virtual ~ASoundManager();
	virtual bool play(const Midi &midi) = 0;
	virtual bool stop(const Midi &midi) = 0;
	virtual bool pause(const Midi &midi) = 0;
	virtual bool setVolume(const int volume) = 0;
	virtual bool stopAll() = 0;
};


#endif  // ASOUNDMANAGER_HH_INCLUDED

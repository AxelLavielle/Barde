/*
  ==============================================================================

    JuceSound.h
    Created: 13 Mar 2017 1:42:58pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef JUCESOUND_HH_INCLUDED
#define JUCESOUND_HH_INCLUDED

#include "JuceHeader.h"
#include "ASoundManager.hh"
#include <Windows.h>

class SoundManager : public ASoundManager
{
public:
	SoundManager();
	virtual ~SoundManager();
	virtual bool play(const Midi &midi);
	virtual bool stop(const Midi &midi);
	virtual bool pause(const Midi &midi);
	virtual bool setVolume(const Midi &midi);
	virtual bool stopAll();
private:
	int			volume = 0;
	MidiOutput	*_midiOutput;
};



#endif  // JUCESOUND_HH_INCLUDED

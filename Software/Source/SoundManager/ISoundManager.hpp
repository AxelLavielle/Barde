/*
  ==============================================================================

    ISoundManager.hpp
    Created: 13 Mar 2017 1:41:42pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef ISOUNDMANAGER_HPP_INCLUDED
#define ISOUNDMANAGER_HPP_INCLUDED
#include <iostream>
#include "../MidiManager/Midi.hh"

class ISoundManager
{
public:
	virtual ~ISoundManager() {};
	virtual bool play(const Midi &midi, int bpm) = 0;
	virtual bool stop(const Midi &midi) const = 0;
	virtual bool pause(const Midi &midi) const = 0;
	virtual bool setVolume(const int volume) = 0;
	virtual bool stopAll() const = 0;
};



#endif  // ISOUNDMANAGER_HPP_INCLUDED

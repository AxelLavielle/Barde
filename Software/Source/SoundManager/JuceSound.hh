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
#include "../Tools.hh"

class SoundManager : public ASoundManager
{
public:
	SoundManager();
	virtual ~SoundManager();
	virtual bool play(const Midi &midi);
	virtual bool stop(const Midi &midi) const;
	virtual bool pause(const Midi &midi) const;
	virtual bool setVolume(const Midi &midi) const;
	virtual bool stopAll() const;
	virtual bool setVolume(const int volume);

private:
	int						volume = 0;
	MidiOutput				*_midiOutput;
	MidiFile				_midiBuff;
	 AudioDeviceManager		_audioManager;

	const MidiMessageSequence		*MidiToMessageSequence(const Midi &midi);
};



#endif  // JUCESOUND_HH_INCLUDED

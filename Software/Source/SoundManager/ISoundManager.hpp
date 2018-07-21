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
#include <vector>
#include <mutex>
#include "../CondVariable.hh"
#include "../Tools.hh"
#include "../MidiManager/Midi.hh"

class ISoundManager
{
public:
	virtual ~ISoundManager() {};
	virtual bool play(const Midi &midi, int bpm, bool &stop) = 0;
	virtual bool stop() = 0;
	virtual bool pause(const Midi &midi) const = 0;
	virtual bool setVolume(const int volume) = 0;
	virtual bool stopAll() const = 0;
	virtual void launch(std::vector<std::pair<Midi, int> > &_gen2playQ, std::mutex &_gen2playM, bool &stop, CondVariable &cond) = 0;
};



#endif  // ISOUNDMANAGER_HPP_INCLUDED

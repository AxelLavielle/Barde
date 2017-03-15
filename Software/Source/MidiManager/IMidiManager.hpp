/*
  ==============================================================================

    IMidiManager.hpp
    Created: 7 Mar 2017 5:24:26pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef IMIDIMANAGER_HPP_INCLUDED
#define IMIDIMANAGER_HPP_INCLUDED

#include <string>
#include "Midi.hh"
#include "../Instrument.hh"

class IMidiManager
{
public:
	virtual ~IMidiManager() {}
	virtual void noteOn(int channel, int noteNumber, float velocity, double time) noexcept = 0;
	virtual void noteOn(const Instrument &instument, int noteNumber, float velocity, double time) noexcept = 0;
	virtual void noteOff(int channel, int noteNumber, float velocity, double time) noexcept = 0;
	virtual void noteOff(const Instrument &instrument, int noteNumber, float velocity, double time) noexcept = 0;
	virtual Midi createMidi() = 0;
	virtual void writeToFile(const std::string filePath) = 0;
	virtual void setTempo(const int bpm, double time) = 0;
	virtual void changeInstrument(const int channel, const int instrumentNb, double time) = 0;
	virtual void changeInstrument(const Instrument &instrument, double time) = 0;
};

#endif  // IMIDIMANAGER_HPP_INCLUDED

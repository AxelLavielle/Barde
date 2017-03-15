/*
  ==============================================================================

    AMidiManager.h
    Created: 7 Mar 2017 5:25:06pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef AMIDIMANAGER_HH_INCLUDED
#define AMIDIMANAGER_HH_INCLUDED

#include "IMidiManager.hpp"

class AMidiManager : public IMidiManager
{
public:
	AMidiManager();
	virtual ~AMidiManager();
	virtual void noteOn(int channel, int noteNumber, float velocity, double time) noexcept = 0;
	virtual void noteOn(const Instrument &instument, int noteNumber, float velocity, double time) noexcept = 0;
	virtual void noteOff(int channel, int noteNumber, float velocity, double time) noexcept = 0;
	virtual void noteOff(const Instrument &instrument, int noteNumber, float velocity, double time) noexcept = 0;
	virtual Midi createMidi() = 0;
	virtual void writeToFile(const std::string filePath) = 0;
	virtual void setTempo(const int bpm, double time) = 0;
	virtual void changeInstrument(const int channel, const int instrumentNb, double time) = 0;
	virtual void changeInstrument(const Instrument &instrument, double time) = 0;

protected:
	Midi	_midi;
};

#endif  // AMIDIMANAGER_HH_INCLUDED

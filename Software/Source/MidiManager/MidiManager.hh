/*
  ==============================================================================

    MidiManager.h
    Created: 7 Mar 2017 5:25:20pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef MIDIMANAGER_HH_INCLUDED
#define MIDIMANAGER_HH_INCLUDED

#include "JuceHeader.h"
#include "AMidiManager.hh"

class MidiManager : public AMidiManager
{
public:
	MidiManager();
	virtual ~MidiManager();
	virtual void noteOn(const int channel, const int noteNumber, const float velocity, const double time) noexcept;
	virtual void noteOn(const Instrument &instument, const int noteNumber, const float velocity, const double time) noexcept;
	virtual void noteOff(const int channel, const int noteNumber, const float velocity, const double time) noexcept;
	virtual void noteOff(const Instrument &instrument, const int noteNumber, const float velocity, const double time) noexcept;
	virtual Midi createMidi();
	virtual void writeToFile(const std::string &filePath);
	virtual void setTempo(const unsigned int bpm, const double time = 0);
	virtual void changeInstrument(const int channel, const int instrumentNb, const double time);
	virtual void changeInstrument(const Instrument &instrument, const double time);

private:
	void addMessageToList(const MidiMessage& message);
	String getMidiMessageDescription(const MidiMessage & m);

	MidiMessageSequence		_midiSequence;
	MidiFile				_midiBuff;
};

#endif  // MIDIMANAGER_HH_INCLUDED

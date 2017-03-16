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
	virtual void noteOn(int channel, int noteNumber, float velocity, double time) noexcept;
	virtual void noteOn(const Instrument &instument, int noteNumber, float velocity, double time) noexcept;
	virtual void noteOff(int channel, int noteNumber, float velocity, double time) noexcept;
	virtual void noteOff(const Instrument &instrument, int noteNumber, float velocity, double time) noexcept;
	virtual Midi createMidi();
	virtual void writeToFile(const std::string filePath);
	virtual void setTempo(const int bpm, double time);
	virtual void changeInstrument(const int channel, const int instrumentNb, double time);
	virtual void changeInstrument(const Instrument &instrument, double time);

private:
	void addMessageToList(const MidiMessage& message);
	String getMidiMessageDescription(const MidiMessage & m);

	MidiMessageSequence		_midiSequence;
	MidiFile				_midiBuff;
};

#endif  // MIDIMANAGER_HH_INCLUDED

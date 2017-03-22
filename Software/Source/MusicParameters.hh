/*
  ==============================================================================

    MusicParameters.h
    Created: 13 Mar 2017 1:47:13pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef MUSICPARAMETERS_HH_INCLUDED
#define MUSICPARAMETERS_HH_INCLUDED

#include <vector>
#include "Instrument.hh"
#include "AI/StyleSettings.hh"
#include "MidiManager/Midi.hh"
#include "MidiManager/MidiManager.hh"

class MusicParameters
{
public:
	MusicParameters();
	~MusicParameters();
	int getBpm() const;
	void setBpm(const int bpm);
	unsigned int getSeed() const;
	void setSeed(const unsigned int seed);
	void addInstrument(const Instrument &instrument);
	std::vector<Instrument>	getInstruments() const;
	void setInstruments(const std::vector<Instrument> &instruments);
	void setStyleName(const std::string &name);
	std::string	getStyleName() const;
	void setMidi(const Midi &midi);
	Midi getMidi() const;
	MidiManager							_midiManager; //THis is bad !! Need modififcation

private:
	unsigned int						_seed;
	int									_bpm;
	std::vector<Instrument>				_instruments;
	std::string							_styleName;
	Midi								_midi;
};


#endif  // MUSICPARAMETERS_HH_INCLUDED

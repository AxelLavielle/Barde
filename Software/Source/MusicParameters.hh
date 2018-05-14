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
	MusicParameters(const MusicParameters &params);
	MusicParameters &operator=(const MusicParameters &params);
	~MusicParameters();
	int getBpm() const;
	void setBpm(const int bpm);
	unsigned int getSeed() const;
	void setSeed(const unsigned int seed);
	void addInstrumentChords(const Instrument &instrument);
	void addInstrumentArpeggios(const Instrument &instrument);
	bool delInstrumentChords(const Instrument &instrument);
	bool delInstrumentArpeggios(const Instrument &instrument);
	void setInstrumentDrums(const bool instrument);
	std::vector<Instrument>	getInstrumentsChords() const;
	std::vector<Instrument>	getInstrumentsArpeggios() const;
	bool	getInstrumentsDrums() const;
	void setInstrumentsChords(const std::vector<Instrument> &instruments);
	void setInstrumentsArpeggios(const std::vector<Instrument> &instruments);
	void setStyleName(const std::string &name);
	std::string	getStyleName() const;


private:
	unsigned int						_seed;
	int									_bpm;
	std::vector<Instrument>				_instrumentsChords;
	std::vector<Instrument>				_instrumentsArpeggios;
	bool								_instrumentsDrums;
	std::string							_styleName;
};


#endif  // MUSICPARAMETERS_HH_INCLUDED

/*
  ==============================================================================

    MusicParameters.cpp
    Created: 13 Mar 2017 1:47:13pm
    Author:  Anthony

  ==============================================================================
*/

#include "MusicParameters.hh"

MusicParameters::MusicParameters()
{
}


MusicParameters::MusicParameters(const MusicParameters &params)
{
	_bpm = params.getBpm();
	_instrumentsArpeggios = params.getInstrumentsArpeggios();
	_instrumentsChords = params.getInstrumentsChords();
	_instrumentsDrums = params.getInstrumentsDrums();
}

MusicParameters &MusicParameters::operator=(const MusicParameters &params)
{
	MusicParameters *n = new MusicParameters();
	n->_bpm = params.getBpm();
	n->_instrumentsArpeggios = params.getInstrumentsArpeggios();
	n->_instrumentsChords = params.getInstrumentsChords();
	n->_instrumentsDrums = params.getInstrumentsDrums();
	return *n;
}

MusicParameters::~MusicParameters()
{
}

int MusicParameters::getBpm() const
{
	return (_bpm);
}

void MusicParameters::setBpm(const int bpm)
{
	_bpm = bpm;
}

unsigned int MusicParameters::getSeed() const
{
	return (_seed);
}

void MusicParameters::setSeed(const unsigned int seed)
{
	_seed = seed;
}

void MusicParameters::addInstrumentChords(const Instrument &instrument)
{
	_instrumentsChords.push_back(instrument);
}

void MusicParameters::addInstrumentArpeggios(const Instrument &instrument)
{
	_instrumentsArpeggios.push_back(instrument);
}

void MusicParameters::setInstrumentDrums(const bool instrument)
{
	_instrumentsDrums = instrument;
}

std::vector<Instrument> MusicParameters::getInstrumentsChords() const
{
	return (_instrumentsChords);
}

std::vector<Instrument> MusicParameters::getInstrumentsArpeggios() const
{
	return (_instrumentsArpeggios);
}

bool MusicParameters::getInstrumentsDrums() const
{
	return (_instrumentsDrums);
}

void MusicParameters::setInstrumentsChords(const std::vector<Instrument> &instruments)
{
	_instrumentsChords = instruments;
}

void MusicParameters::setInstrumentsArpeggios(const std::vector<Instrument> &instruments)
{
	_instrumentsArpeggios = instruments;
}

void MusicParameters::setStyleName(const std::string & name)
{
	_styleName = name;
}

std::string MusicParameters::getStyleName() const
{
	return (_styleName);
}

void MusicParameters::setMidi(const Midi & midi)
{
	_midi = midi;
}

Midi MusicParameters::getMidi() const
{
	return (_midi);
}

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

void MusicParameters::addInstrument(const Instrument &instrument)
{
	_instruments.push_back(instrument);
}

std::vector<Instrument> MusicParameters::getInstruments() const
{
	return (_instruments);
}

void MusicParameters::setInstruments(const std::vector<Instrument> &instruments)
{
	_instruments = instruments;
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

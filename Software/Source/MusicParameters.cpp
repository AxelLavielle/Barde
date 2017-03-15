/*
  ==============================================================================

    MusicParameters.cpp
    Created: 13 Mar 2017 1:47:13pm
    Author:  Anthony

  ==============================================================================
*/

#include "MusicParameters.hh"

MusicParameter::MusicParameter()
{
}

MusicParameter::~MusicParameter()
{
}

int MusicParameter::getBpm() const
{
	return (_bpm);
}

void MusicParameter::setBpm(const int bpm)
{
	_bpm = bpm;
}

int MusicParameter::getSeed() const
{
	return (_seed);
}

void MusicParameter::setSeed(const int seed)
{
	_seed = seed;
}

void MusicParameter::addInstrument(const Instrument &instrument)
{
	_instruments.push_back(instrument);
}

std::vector<Instrument> MusicParameter::getInstruments() const
{
	return (_instruments);
}

void MusicParameter::setInstruments(const std::vector<Instrument> &instruments)
{
	_instruments = instruments;
}

void MusicParameter::setStyleName(const std::string & name)
{
	_styleName = name;
}

std::string MusicParameter::getStyleName() const
{
	return (_styleName);
}

void MusicParameter::setMidi(const Midi & midi)
{
	_midi = midi;
}

Midi MusicParameter::getMidi() const
{
	return (_midi);
}

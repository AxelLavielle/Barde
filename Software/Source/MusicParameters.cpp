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
	_bpm = 105;
	_drums = false;
}


MusicParameters::MusicParameters(const MusicParameters &params)
{
	_bpm = params.getBpm();
	_drums = params.getDrums();
	_instrumentsArpeggios = params.getInstrumentsArpeggios();
	_instrumentsChords = params.getInstrumentsChords();
	_instrumentsDrums = params.getInstrumentsDrums();
}

MusicParameters &MusicParameters::operator=(const MusicParameters &params)
{
	_bpm = params.getBpm();
	_drums = params.getDrums();
	_instrumentsArpeggios = params.getInstrumentsArpeggios();
	_instrumentsChords = params.getInstrumentsChords();
	_instrumentsDrums = params.getInstrumentsDrums();
	return *this;
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

void MusicParameters::addInstrumentDrums(const Instrument &instrument)
{
	_instrumentsDrums.push_back(instrument);
}

bool MusicParameters::delInstrumentChords(const Instrument &instrument)
{
	for (unsigned int i = 0; i < _instrumentsChords.size(); i++)
		if (_instrumentsChords[i].nb == instrument.nb)
		{
			_instrumentsChords.erase(_instrumentsChords.begin() + i);
			return (true);
		}
return (false);
}

bool MusicParameters::delInstrumentArpeggios(const Instrument &instrument)
{
	for (unsigned int i = 0; i < _instrumentsArpeggios.size(); i++)
		if (_instrumentsArpeggios[i].nb == instrument.nb)
		{
			_instrumentsArpeggios.erase(_instrumentsArpeggios.begin() + i);
			return (true);
		}
	return (false);
}

std::vector<Instrument> MusicParameters::getInstrumentsChords() const
{
	return (_instrumentsChords);
}

std::vector<Instrument> MusicParameters::getInstrumentsArpeggios() const
{
	return (_instrumentsArpeggios);
}

std::vector<Instrument> MusicParameters::getInstrumentsDrums() const
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

void MusicParameters::setInstrumentsDrums(const std::vector<Instrument> &instruments)
{
	_instrumentsDrums = instruments;
}

void MusicParameters::setDrums(const bool drums)
{
	_drums = drums;
}

bool MusicParameters::getDrums() const
{
	return(_drums);
}

void MusicParameters::setStyleName(const std::string & name)
{
	_styleName = name;
}

std::string MusicParameters::getStyleName() const
{
	return (_styleName);
}

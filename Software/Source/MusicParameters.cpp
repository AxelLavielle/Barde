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
	_instrumentsDrums = false;
	initFreeChannels();
}


MusicParameters::MusicParameters(const MusicParameters &params)
{
	_bpm = params.getBpm();
	_styleName = params.getStyleName();
	_seed = params.getSeed();
	_instrumentsArpeggios = params.getInstrumentsArpeggios();
	_instrumentsChords = params.getInstrumentsChords();
	_instrumentsDrums = params.getInstrumentsDrums();
	std::memcpy(&_freeChannels[0], params.getFreeChannels(), NB_OF_CHANNEL);
}

MusicParameters &MusicParameters::operator=(const MusicParameters &params)
{
	_bpm = params.getBpm();
	_styleName = params.getStyleName();
	_seed = params.getSeed();
	_instrumentsArpeggios = params.getInstrumentsArpeggios();
	_instrumentsChords = params.getInstrumentsChords();
	_instrumentsDrums = params.getInstrumentsDrums();
	std::memcpy(&_freeChannels[0], params.getFreeChannels(), NB_OF_CHANNEL);
	return *this;
}

MusicParameters::~MusicParameters()
{
}

void MusicParameters::initFreeChannels()
{
	for (size_t i = 0; i < NB_OF_CHANNEL; i++)
	{
		_freeChannels[i] = 0;
	}
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
	_freeChannels[instrument.channel - 1] = 1;
}

void MusicParameters::addInstrumentArpeggios(const Instrument &instrument)
{
	_instrumentsArpeggios.push_back(instrument);
	_freeChannels[instrument.channel - 1] = 1;
}

bool MusicParameters::delInstrumentChords(const Instrument &instrument)
{
	for (unsigned int i = 0; i < _instrumentsChords.size(); i++)
		if (_instrumentsChords[i].nb == instrument.nb)
		{
			_freeChannels[_instrumentsChords[i].channel - 1] = 0;
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
			_freeChannels[_instrumentsArpeggios[i].channel - 1] = 0;
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

bool MusicParameters::getInstrumentsDrums() const
{
	return (_instrumentsDrums);
}

void MusicParameters::setInstrumentsChords(const std::vector<Instrument> &instruments)
{
	std::vector<Instrument>::const_iterator		it;

	_instrumentsChords = instruments;
	for (it = instruments.begin(); it != instruments.end(); it++)
	{
		_freeChannels[it->channel - 1] = 1;
	}
}

void MusicParameters::setInstrumentsArpeggios(const std::vector<Instrument> &instruments)
{
	std::vector<Instrument>::const_iterator		it;

	_instrumentsArpeggios = instruments;
	for (it = instruments.begin(); it != instruments.end(); it++)
	{
		_freeChannels[it->channel - 1] = 1;
	}
}

void MusicParameters::setInstrumentsDrums(const bool instruments)
{
	_instrumentsDrums = instruments;
}

void MusicParameters::setStyleName(const std::string & name)
{
	_styleName = name;
}

std::string MusicParameters::getStyleName() const
{
	return (_styleName);
}

int MusicParameters::getFreeChannel() const
{
	for (size_t i = 0; i < 128; i++)
	{
		if (_freeChannels[i] == 0)
		{
			return i + 1;
		}
	}
	return -1;
}

const short *MusicParameters::getFreeChannels() const
{
	return (_freeChannels);
}
